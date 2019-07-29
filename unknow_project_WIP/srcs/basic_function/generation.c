#include "unknow_project.h"

int		generate_nbr(int min, int max)
{
	int	value;
	int	tmp;

	if (min < 0)
		max += -min;
	value = rand();

	value = value % max;
	value += min;

	return (value);
}
