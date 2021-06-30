#include "chain.h"
#include <iostream>


void chain::swap_or_not( chain* ch )
{
  cout_mutex.lock();
  std::cout << "chain " << id << " swapped (or not) with chain " << ch->id << "\n";
  cout_mutex.unlock();
}  


void chain::run()
{
  cout_mutex.lock();
  std::cout << "chain " << id << " run\n";
  cout_mutex.unlock();
}
