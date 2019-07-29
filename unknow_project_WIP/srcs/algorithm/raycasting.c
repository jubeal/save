# include "unknow_project.h"


t_vector3_list	*bresenham_3d(t_vector3 start, t_vector3 end)
{
	int dx, dy, dz, xs, ys, zs, p1, p2;
    t_vector3_list *list_of_points;

	list_of_points = initialize_t_vector3_list();
    t_vector3_list_push_back(list_of_points, start);
    dx = ft_abs_float(end.x - start.x);
    dy = ft_abs_float(end.y - start.y);
    dz = ft_abs_float(end.z - start.z);
    if (end.x > start.x)
        xs = 1;
    else
        xs = -1;
    if (end.y > start.y)
        ys = 1;
    else
        ys = -1;
    if (end.z > start.z)
        zs = 1;
    else
        zs = -1;
    // Driving axis is X-axis
    if (dx >= dy && dx >= dz)
    {
	    p1 = 2 * dy - dx;
        p2 = 2 * dz - dx;
        while (start.x != end.x)
        {
		    start.x += xs;
            if (p1 >= 0)
            {
			    start.y += ys;
                p1 -= 2 * dx;
			}
			if (p2 >= 0)
            {
			    start.z += zs;
                p2 -= 2 * dx;
			}
			p1 += 2 * dy;
            p2 += 2 * dz;
			t_vector3_list_push_back(list_of_points, start);
		}
	}
    // Driving axis is Y-axis
    else if (dy >= dx && dy >= dz)
    {
		p1 = 2 * dx - dy;
        p2 = 2 * dz - dy;
        while (start.y != end.y)
		{
            start.y += ys;
            if (p1 >= 0)
			{
                start.x += xs;
                p1 -= 2 * dy;
			}
			if (p2 >= 0)
            {
			    start.z += zs;
                p2 -= 2 * dy;
			}
			p1 += 2 * dx;
            p2 += 2 * dz;
			t_vector3_list_push_back(list_of_points, start);
		}
	}
    // Driving axis is Z-axis"
    else
	{
        p1 = 2 * dy - dz;
        p2 = 2 * dx - dz;
        while (start.z != end.z)
		{
            start.z += zs;
            if (p1 >= 0)
            {
				start.y += ys;
                p1 -= 2 * dz;
			}
			if (p2 >= 0)
            {
				start.x += xs;
                p2 -= 2 * dz;
			}
			p1 += 2 * dy;
            p2 += 2 * dx;
			t_vector3_list_push_back(list_of_points, start);
		}
	}
	return (list_of_points);
}

t_mesh	*cast_ray(t_engine *engine, t_vector3 pos, t_vector3 direction)
{
	int 		i;
	int 		j;
	int 		k;
	float		subdivision = 3;
	t_vector3	dest_pos;
	t_line		line;
	t_triangle	triangle;
	t_vector3	intersection;
	t_mesh 		*mesh;
	t_face		*face;

	i = 0;
	direction = divide_vector3_by_float(direction, subdivision);
	direction = normalize_t_vector3(direction);
	while (i < FAR * subdivision)
	{
		j = 0;
		dest_pos = add_vector3_to_vector3(pos, direction);
		// print_t_vector3(pos, "--------\npos");
		// print_t_vector3(direction, "dir");
		// print_t_vector3(dest_pos, "dest_pos");
		while (j < t_engine_return_mesh_len(engine))
		{
			k = 0;
			mesh = t_engine_get_mesh(engine, j);
			line = create_t_line(pos, dest_pos);
			while (k < mesh->faces->size)
			{
				face = t_face_list_get(mesh->faces, k);
				triangle = compose_t_triangle_from_t_mesh(mesh, face->index_vertices);
				if (intersect_triangle_by_segment(triangle, face->normale, line, &intersection) == BOOL_TRUE)
				{
					// printf("HIT : %d\n", j);
					return (mesh);
				}
				k++;
			}
			j++;
		}
		pos = dest_pos;
		i++;
	}
	return (NULL);
}
