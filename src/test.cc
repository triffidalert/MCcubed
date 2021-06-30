#include <thread>
#include <iostream>
#include <vector>
#include "pair_barrier.h"

constexpr int num_chains{4};

chain c[num_chains];
std::thread th[num_chains];

std::mutex cout_mutex;

double log_target( double x )
{
  double ret;
  ret = (x + 5)*(x + 5)/(2 * 0.3 * 0.3);
  ret += (x - 5)*(x - 5)/(2 * 6.0 * 6.0);
  ret += x * x / (2 * 1000.0 * 1000.0 );
  return -ret;
}

void f( chain* ch, std::vector<pair_barrier>& barriers )
{
  std::vector<pair_barrier>::iterator it{barriers.begin()}, itend{barriers.end()};

  for(; it != itend; ++it)
    {
      ch->run();
      cout_mutex.lock();
      std::cout << "chain " << ch->id << " running to barrier ("
		<< it->id_1 << "," << it->id_2 << ")" << std::endl;
      cout_mutex.unlock();
      pass_through_barrier( ch, *it );
    }
  
  
}

using namespace std;

int main()
{

  vector<pair_barrier> barriers;
  barriers.push_back( pair_barrier( 0, 1, num_chains ));
  barriers.push_back( pair_barrier( 2, 3, num_chains ));
  barriers.push_back( pair_barrier( 0, 3, num_chains ));
		        
  for( int i{0}; i < num_chains; ++i ) c[i].id = i;

  for( int i{0}; i < num_chains; ++i ) th[i] = std::thread( f, c + i, std::ref(barriers) );
  for( int i{0}; i < num_chains; ++i ) th[i].join();
  



}//int main()
