#include "unknow_project.h"

t_line	create_t_line(t_vector4 p_a, t_vector4 p_b)
{
	t_line	result;

	result.a = p_a;
	result.b = p_b;
	return (result);
}

t_line	*initialize_t_line(t_vector4 p_a, t_vector4 p_b)
{
	t_line	*result;

	if (!(result = (t_line *)malloc(sizeof(t_line))))
		error_exit(-31, "Can't malloc a t_line");
	// printf("malloc t_line\n");
	*result = create_t_line(p_a, p_b);
	return (result);
}

void	print_t_line(t_line line, char *str)
{
	// printf("Line : %s\n", str);
	print_t_vector4(line.a, "Point A");
	print_t_vector4(line.b, "Point B");
}
