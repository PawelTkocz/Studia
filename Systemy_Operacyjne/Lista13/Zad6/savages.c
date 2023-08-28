#include "csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

#define N 5
#define M 5

static struct {
  /* TODO: Put semaphores and shared variables here. */
  int meals;
  sem_t mutex;
  sem_t empty_pot;
  sem_t full_pot;
} *shared = NULL;


static void savage(void) {
  for (;;) {
    /* TODO Take a meal or wait for it to be prepared. */
    Sem_wait(&shared->mutex);
    if(shared->meals==0){
      Sem_post(&shared->empty_pot);
      Sem_wait(&shared->full_pot);
    }
    shared->meals -= 1;
    outc('+');
    Sem_post(&shared->mutex);
    /* Sleep and digest. */
    usleep(rand() % 1000 + 1000);
  }

  exit(EXIT_SUCCESS);
}

static void cook(void) {
  for (;;) {
    /* TODO Cook is asleep as long as there are meals.
     * If woken up they cook exactly M meals. */
    Sem_wait(&shared->empty_pot);
    outc('-');
    shared->meals = M;
    Sem_post(&shared->full_pot);  
  }
}

/* Do not bother cleaning up after this process. Let's assume that controlling
 * terminal sends SIGINT to the process group on CTRL+C. */
int main(void) {
  shared = Mmap(NULL, getpagesize(), PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED,
                -1, 0);

  /* TODO: Initialize semaphores and other shared state. */
  shared->meals = 0;
  Sem_init(&shared->empty_pot, 1, 0);
  Sem_init(&shared->full_pot, 1, 0);
  Sem_init(&shared->mutex, 1, 1);

  for (int i = 0; i < N; i++)
    if (Fork() == 0)
      savage();

  cook();

  return EXIT_SUCCESS;
}
