#include "unknow_project.h"

t_door	create_t_door(void)
{
	t_door	result;

    result.tick = 0;
	result.state = 0;
    result.move = 0;
	return (result);
}

t_door	*initialize_t_door(void)
{
	t_door	*result;

	if (!(result = (t_door *)malloc(sizeof(t_door))))
		return (NULL);
	// printf("malloc t_door\n");
	*result = create_t_door();
	return (result);
}
