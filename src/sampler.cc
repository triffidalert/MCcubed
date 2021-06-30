#include "chain.h"

void sampler::calc_current_like()
{
	double ll;
	ll = -(current + 5)*(current + 5)/(2 * .3 * .3);
	ll -= (current - 5)*(current - 5)/(2 * 6.0 * 6.0);
	ll -= current*current/(2 * 1000.0 * 1000.0);

}


sampler::sampler(double initial)
	:current{initial}
	{
		calc_current_like();
	};

