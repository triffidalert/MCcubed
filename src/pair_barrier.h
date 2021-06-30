#ifndef BARRIER_H
#define BARRIER_H

#include <semaphore.h>
#include <mutex>
#include "chain.h"

extern std::mutex cout_mutex;

struct pair_barrier{
 
  const int id_1, id_2;
  int n;
  int threads_through;
  int flag;
  sem_t mutex1;
  sem_t mutex2;
  sem_t barrier;

  chain* held_chain;
  
  pair_barrier( const int i1, const int i2, int total_threads );
  void wait();
};

void pass_through_barrier( chain*, pair_barrier& );

#endif ///BARRIER_H
