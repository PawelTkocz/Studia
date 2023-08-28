#include "csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

typedef struct {
  /* TODO: Use this structure to store barrier internal state. */
  int waiting;
  int max_count;
  int started;
  int finished;
  sem_t mutex;
  sem_t barrier;
  sem_t barrier2;
} barrier_t;

static barrier_t *barrier_init(int n) {
  if (n < 1)
    app_error("barrier_init requires n > 0");

  barrier_t *b = Mmap(NULL, sizeof(barrier_t), PROT_READ|PROT_WRITE,
                      MAP_ANON|MAP_SHARED, -1, 0);

  /* TODO: Initialize barrier internal state. */
  Sem_init(&b->barrier, 1, 0);
  Sem_init(&b->barrier2, 1, 0);
  Sem_init(&b->mutex, 1, 1);
  b->waiting = 0;
  b->finished = 0;
  b->max_count = n;
  b->started = 0;
  return b;
}

static void barrier_wait(barrier_t *b) {
  /* TODO: Provide wait procedure implementation here. */
  
  Sem_wait(&b->mutex);
  b->waiting += 1;
  if(b->waiting==b->max_count){
    Sem_post(&b->barrier);
    b->waiting = 0;
  }
  Sem_post(&b->mutex);
  Sem_wait(&b->barrier);


  Sem_wait(&b->mutex);
  b->started += 1;
  if(b->started == b->max_count){
    b->started = 0;
    Sem_post(&b->barrier2);
  }
  else
    Sem_post(&b->barrier);
  Sem_post(&b->mutex);
  Sem_wait(&b->barrier2);

  Sem_wait(&b->mutex);
  b->finished += 1;
  outc('*');
  if(b->finished != b->max_count)
    Sem_post(&b->barrier2);
  else{
    b->finished = 0;
    outc(10);
  }
  Sem_post(&b->mutex);
}

static void barrier_destroy(barrier_t *b) {
  /* TODO: Provide destroy procedure implementation here. */
  sem_destroy(&b->barrier2);
  sem_destroy(&b->barrier);
  sem_destroy(&b->mutex);
}

#define K 100
#define N 50
#define P 100

static noreturn void horse(barrier_t *b) {
  int n = rand() % K + K;

  outc('+');

  for (int i = 0; i < n; i++) {
    barrier_wait(b);
    usleep(rand() % 2000 + 1000);
  }

  outc('-');

  exit(EXIT_SUCCESS);
}

/* Do not bother cleaning up after this process. Let's assume that controlling
 * terminal sends SIGINT to the process group on CTRL+C. */
int main(void) {
  barrier_t *b = barrier_init(N);

  int horses = 0;

  for (;;) {
    do {
      if (Fork() == 0) {
        srand(getpid());
        horse(b);
      }
      horses++;
    } while (horses < P);

    Wait(NULL);
    horses--;
  }

  barrier_destroy(b);

  return EXIT_SUCCESS;
}
