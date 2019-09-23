# include "unknow_project.h"

t_mesh	*cast_ray_next(t_engine *engine, t_vector3 pos, t_vector3 direction, t_mesh *mesh)
{
	int 		k;
	t_line		line;
	t_vector3	intersection;

	k = -1;
	line = create_t_line(pos, add_vector3_to_vector3(pos, direction));
	while (++k < mesh->faces->size)
	{
		if (intersect_triangle_by_segment(compose_t_triangle_from_t_mesh
				(mesh, t_face_list_get(mesh->faces, k)->index_vertices),
				t_face_list_get(mesh->faces, k)->normale, line,
				&intersection) == BOOL_TRUE)
			return (mesh);
	}
	return (NULL);
}

t_mesh	*cast_ray(t_engine *engine, t_vector3 pos, t_vector3 direction)
{
	int 		i;
	int 		j;
	t_mesh 		*mesh;

	i = -1;
	direction = normalize_t_vector3(direction);
	direction = divide_vector3_by_float(direction, 3);
	while (++i < FAR * 3)
	{
		j = -1;
		while (++j < t_engine_return_mesh_len(engine))
		{
			mesh = t_engine_get_mesh(engine, j);
			mesh = cast_ray_next(engine, pos, direction, mesh);
		}
		pos = add_vector3_to_vector3(pos, direction);
	}
	return (NULL);
}
