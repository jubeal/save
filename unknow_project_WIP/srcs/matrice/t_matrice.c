#include "unknow_project.h"

t_matrix	create_t_matrix(void)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (j != i)
				result.value[i][j] = 0.0f;
			else
				result.value[i][j] = 1.0f;
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix	create_t_matrix_empty(void)
{
	t_matrix	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.value[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix	*initialize_t_matrix(void)
{
	t_matrix	*result;

	if (!(result = (t_matrix *)malloc(sizeof(t_matrix))))
		error_exit(-13, "Can't create a t_matrix array");
	// printf("malloc t_matrix\n");
	*result = create_t_matrix();
	return (result);
}

t_matrix	create_translation_matrix(t_vector3 translation)
{
	t_matrix	result;

	result = create_t_matrix();
	result.value[3][0] = translation.x;
	result.value[3][1] = translation.y;
	result.value[3][2] = translation.z;
	return (result);
}

t_matrix	create_scaling_matrix(t_vector3 scaling)
{
	t_matrix	result;

	result = create_t_matrix();
	result.value[0][0] = scaling.x;
	result.value[1][1] = scaling.y;
	result.value[2][2] = scaling.z;
	return (result);
}

t_matrix	create_rotation_x_matrix(float angle)
{
	t_matrix	result;
	float		radian;

	result = create_t_matrix();
	radian = degree_to_radius(angle);
	result.value[1][1] = cos(radian);
	result.value[2][1] = -sin(radian);
	result.value[1][2] = sin(radian);
	result.value[2][2] = cos(radian);
	return (result);
}

t_matrix	create_rotation_y_matrix(float angle)
{
	t_matrix	result;
	float		radian;

	result = create_t_matrix();
	radian = degree_to_radius(angle);
	result.value[0][0] = cos(radian);
	result.value[0][2] = -sin(radian);
	result.value[2][0] = sin(radian);
	result.value[2][2] = cos(radian);
	return (result);
}

t_matrix	create_rotation_z_matrix(float angle)
{
	t_matrix	result;
	float		radian;

	result = create_t_matrix();
	radian = degree_to_radius(angle);
	result.value[0][0] = cos(radian);
	result.value[0][1] = sin(radian);
	result.value[1][0] = -sin(radian);
	result.value[1][1] = cos(radian);
	return (result);
}

t_matrix	create_rotation_matrix(float x, float y, float z)
{
	t_matrix	tmp[4];
	t_matrix	result;

	tmp[0] = create_rotation_x_matrix(x);
	tmp[1] = create_rotation_y_matrix(y);
	tmp[2] = create_rotation_z_matrix(z);
	tmp[3] = mult_matrix_by_matrix(tmp[0], tmp[1]);
	result = mult_matrix_by_matrix(tmp[3], tmp[2]);
	return (result);
}

t_matrix	mult_matrix_by_matrix(t_matrix m1, t_matrix m2)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	result = create_t_matrix_empty();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.value[j][i] = (m1.value[0][i] * m2.value[j][0]) \
								+ (m1.value[1][i] * m2.value[j][1]) \
								+ (m1.value[2][i] * m2.value[j][2]) \
								+ (m1.value[3][i] * m2.value[j][3]);
			j++;
		}
		i++;
	}
	return (result);
}

t_vector3	mult_vector3_by_matrix(t_vector3 vertex, t_matrix m)
{
	float	result[3];

	result[0] = m.value[0][0] * vertex.x + m.value[1][0] * vertex.y \
							+ m.value[2][0] * vertex.z + m.value[3][0];
	result[1] = m.value[0][1] * vertex.x + m.value[1][1] * vertex.y \
							+ m.value[2][1] * vertex.z + m.value[3][1];
	result[2] = m.value[0][2] * vertex.x + m.value[1][2] * vertex.y \
							+ m.value[2][2] * vertex.z + m.value[3][2];
	return (create_t_vector3(result[0], result[1], result[2]));
}

void		print_t_matrix(t_matrix *m)
{
	int	i;

	i = 0;
	// printf("--------------------------------------------------------------\n");
	while (i < 4)
	{
		// printf("|\t%-.2f|\t%-.2f|\t%-.2f|\t%-.2f|\n", m->value[0][i],\
				m->value[1][i], m->value[2][i], m->value[3][i]);
		i++;
	}
	// printf("--------------------------------------------------------------\n");
}
