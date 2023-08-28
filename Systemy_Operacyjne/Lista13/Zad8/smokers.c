#include "csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

static __thread unsigned seed;

static sem_t tobacco;
static sem_t matches;
static sem_t paper;
static sem_t doneSmoking;

/* TODO: If you need any extra global variables, then define them here. */
static bool is_tobacco;
static bool are_matches;
static bool is_paper;
static sem_t tobacco_smoker;
static sem_t paper_smoker;
static sem_t matches_smoker;
static sem_t mutex;

static void *agent(void *arg) {
  seed = pthread_self();

  while (true) {
    Sem_wait(&doneSmoking);

    int choice = rand_r(&seed) % 3;
    if (choice == 0) {
      Sem_post(&tobacco);
      Sem_post(&paper);
    } else if (choice == 1) {
      Sem_post(&tobacco);
      Sem_post(&matches);
    } else {
      Sem_post(&paper);
      Sem_post(&matches);
    }
  }

  return NULL;
}

/* TODO: If you need extra threads, then define their main procedures here. */

static void *pusher_tobacco(void *arg){
  while(1){
    Sem_wait(&tobacco);
    Sem_wait(&mutex);
    if(is_paper){
      is_paper = false;
      Sem_post(&matches_smoker);
    }
    else if(are_matches){
      are_matches = false;
      Sem_post(&paper_smoker);
    }
    else
      is_tobacco = true;
    Sem_post(&mutex);
  }
  return NULL;
}

static void *pusher_paper(void *arg){
  while(1){
    Sem_wait(&paper);
    Sem_wait(&mutex);
    if(is_tobacco){
      is_tobacco = false;
      Sem_post(&matches_smoker);
    }
    else if(are_matches){
      are_matches = false;
      Sem_post(&tobacco_smoker);
    }
    else
      is_paper = true;
    Sem_post(&mutex);
  }
  return NULL;
}

static void *pusher_matches(void *arg){
  while(1){
    Sem_wait(&matches);
    Sem_wait(&mutex);
    if(is_tobacco){
      is_tobacco = false;
      Sem_post(&paper_smoker);
    }
    else if(is_paper){
      is_paper = false;
      Sem_post(&tobacco_smoker);
    }
    else
      are_matches = true;
    Sem_post(&mutex);
  }
  return NULL;
}

static void randsleep(void) {
  usleep(rand_r(&seed) % 1000 + 1000);
}

static void make_and_smoke(char smoker) {
  randsleep();
  Sem_post(&doneSmoking);
  outc(smoker);
  randsleep();
}

static void *smokerWithMatches(void *arg) {
  seed = pthread_self();

  while (true) {
    /* TODO: wait for paper and tobacco */
    Sem_wait(&matches_smoker);
    make_and_smoke('M');
  }

  return NULL;
}

static void *smokerWithTobacco(void *arg) {
  seed = pthread_self();

  while (true) {
    /* TODO: wait for paper and matches */
    Sem_wait(&tobacco_smoker);
    make_and_smoke('T');
  }

  return NULL;
}

static void *smokerWithPaper(void *arg) {
  seed = pthread_self();
 
  while (true) {
    /* TODO: wait for tobacco and matches */
    Sem_wait(&paper_smoker);
    make_and_smoke('P');
  }

  return NULL;
}

int main(void) {
  Sem_init(&tobacco, 0, 0);
  Sem_init(&matches, 0, 0);
  Sem_init(&paper, 0, 0);
  Sem_init(&doneSmoking, 0, 1);

  /* TODO: Initialize your global variables here. */
  is_paper = false;
  is_tobacco = false;
  are_matches = false;
  Sem_init(&tobacco_smoker, 0, 0);
  Sem_init(&matches_smoker, 0, 0);
  Sem_init(&paper_smoker, 0, 0);
  Sem_init(&mutex, 0, 1);
  pthread_t pusher_tobacco_thread, pusher_paper_thread, pusher_matches_thread;
  Pthread_create(&pusher_tobacco_thread, NULL, pusher_tobacco, NULL);
  Pthread_create(&pusher_paper_thread, NULL, pusher_paper, NULL);
  Pthread_create(&pusher_matches_thread, NULL, pusher_matches, NULL);

  pthread_t agentThread;
  Pthread_create(&agentThread, NULL, agent, NULL);

  pthread_t smokerPaperThread, smokerMatchesThread, smokerTobaccoThread;
  Pthread_create(&smokerPaperThread, NULL, smokerWithPaper, NULL);
  Pthread_create(&smokerMatchesThread, NULL, smokerWithMatches, NULL);
  Pthread_create(&smokerTobaccoThread, NULL, smokerWithTobacco, NULL);

  Pthread_join(agentThread, NULL);
  Pthread_join(smokerPaperThread, NULL);
  Pthread_join(smokerMatchesThread, NULL);
  Pthread_join(smokerTobaccoThread, NULL);
  Pthread_join(pusher_tobacco_thread, NULL);
  Pthread_join(pusher_paper_thread, NULL);
  Pthread_join(pusher_matches_thread, NULL);

  return 0;
}
