#include "unknow_project.h"

void		sat_test(t_vector3 normale, t_vector3_list *vector_list, float *min, float *max)
{
	int		i;
	float	dot_result;

	*min = INT_MAX;
	*max = INT_MIN;
	i = 0;
	while (i < vector_list->size)
	{
		dot_result = dot_t_vector3(normale, t_vector3_list_at(vector_list, i));
		if (dot_result < *min)
			*min = dot_result;
		if (dot_result > *max)
			*max = dot_result;
		i++;
	}
}

int		is_t_mesh_intersecting(t_mesh *mesh_compared, t_mesh *mesh_target)
{
	int		i;
	float	value[4];

	i = 0;
	while (i < mesh_compared->faces->size)
	{
		sat_test(t_face_list_get(mesh_compared->faces, i)->normale, mesh_compared->next_vertices_in_world, &(value[0]), &(value[1]));
		sat_test(t_face_list_get(mesh_compared->faces, i)->normale, mesh_target->vertices_in_world, &(value[2]), &(value[3]));
		if (!is_middle(value[0], value[1], value[2]) && !is_middle(value[2], value[3], value[0]))
			return (BOOL_FALSE);
		i++;
	}
	i = 0;
	while (i < mesh_target->faces->size)
	{
		sat_test(t_face_list_get(mesh_target->faces, i)->normale, mesh_compared->next_vertices_in_world, &(value[0]), &(value[1]));
		sat_test(t_face_list_get(mesh_target->faces, i)->normale, mesh_target->vertices_in_world, &(value[2]), &(value[3]));
		if (!is_middle(value[0], value[1], value[2]) && !is_middle(value[2], value[3], value[0]))
			return (BOOL_FALSE);
		i++;
	}
	return (BOOL_TRUE);
}
