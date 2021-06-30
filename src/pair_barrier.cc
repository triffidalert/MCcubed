#include "pair_barrier.h"
#include <iostream>

pair_barrier::pair_barrier( const int i1, const int i2, int total_threads )
  :id_1{i1},
   id_2{i2},
   n{total_threads},
   threads_through{0},
   flag{0},
   held_chain{nullptr}
  {
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&barrier, 0, 0);
  }

//Modification of Barrier (Little Book of Semaphores)
void pass_through_barrier( chain* ch, pair_barrier& ba )
{
  //increment grand counter for later clean-up purposes
  sem_wait( &ba.mutex1 );
  ++ba.threads_through;
  sem_post( &ba.mutex1 );

  //if chain is not one of id_1 or id_2 then pass through
  //otherwise...
  if( ch->id == ba.id_1 or ch->id == ba.id_2 )
    {
      //...increment flag - if first of pair to arrive, set held_chain
      sem_wait( &ba.mutex2 );
      if( ba.flag == 0 ) ba.held_chain = ch;
      ++ba.flag;
      sem_post( &ba.mutex2 );

      if(ba.flag == 2)
	{
	  //held chain is waiting on ba->barrier - swap, perhaps?
	  ch->swap_or_not( ba.held_chain );
	  //trigger non-deadlocking release 
	  sem_post( &ba.barrier );
	}

      sem_wait( &ba.barrier );
      sem_post( &ba.barrier );
    }

  else
    {
      cout_mutex.lock();
      std::cout << "chain " << ch->id << " passed through ("
		<< ba.id_1 << "," << ba.id_2 << ")" << std::endl;
      cout_mutex.unlock();
      return;
    }

}
  //needs to look inside object to get an identity.  Rethink.

