#include "time_exe.h"

double				cl(clock_t t)
{
	static double	last;
	double			m;

	m = ((double)(t - last)) / (CLOCKS_PER_SEC);
	last = ((double)(clock()));
	return (m);
}