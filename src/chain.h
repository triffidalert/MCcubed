#ifndef CHAIN_H
#define CHAIN_H

#include <mutex>

extern std::mutex cout_mutex;

struct chain{
  int id;
  
  void run();
  void swap_or_not( chain* );
};


struct sampler : chain
{
	double current;
	double proposed;

	double current_like;
	double proposed_like;

	sampler(double initial);

	virtual void propose();
	virtual void calc_current_like();
	virtual void calc_proposed_like();


};

#endif //CHAIN_H
