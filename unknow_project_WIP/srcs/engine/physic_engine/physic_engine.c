# include "unknow_project.h"

t_physic_engine	create_t_physic_engine()
{
	t_physic_engine	result;

	result.gravity_force = create_t_vector3(0, -GRAVITY * 3, 0);
	result.mesh_list = initialize_t_mesh_list();

	return (result);
}

t_physic_engine	*initialize_t_physic_engine()
{
	t_physic_engine	*result;

	if (!(result = (t_physic_engine	*)malloc(sizeof(t_physic_engine))))
		return (NULL);

	*result = create_t_physic_engine();

	return (result);
}

void			delete_t_physic_engine(t_physic_engine dest)
{
	free_t_mesh_list(dest.mesh_list);
}

void			free_t_physic_engine(t_physic_engine *dest)
{
	delete_t_physic_engine(*dest);
	free(dest);
}

void			t_physic_engine_draw_mesh(t_physic_engine *p_physic_engine, t_camera *p_cam)
{
	int			i;

	i = 0;
	while (i < p_physic_engine->mesh_list->size)
	{
		draw_t_mesh(p_cam, t_mesh_list_get(p_physic_engine->mesh_list, i));
		i++;
	}
}

void			t_physic_engine_add_mesh(t_physic_engine *physic_engine, t_mesh p_mesh)
{
	t_mesh_list_push_back(physic_engine->mesh_list, p_mesh);
}

t_mesh			*t_physic_engine_get_mesh(t_physic_engine *physic_engine, int index)
{
	return (t_mesh_list_get(physic_engine->mesh_list, index));
}

int				can_move_axis(t_mesh *mesh, t_mesh *target, t_vector3 axis)
{
	int			result;
	t_vector3	tmp;
	t_triangle	triangle_mesh;
	t_triangle	triangle_mesh2;
	t_triangle	triangle_target;
	t_face		*mesh_face;
	t_face		*target_face;
	t_vector3	delta_pos;
	int			i;
	int			j;

	result = 0;
	tmp = mult_vector3_by_vector3(mesh->force, axis);
	delta_pos = add_vector3_to_vector3(mesh->pos, tmp);
	clean_t_vector3_list(mesh->vertices_in_world);
	i = 0;
	while (i < mesh->vertices->size)
	{
		t_vector3_list_push_back(mesh->vertices_in_world, add_vector3_to_vector3(t_vector3_list_at(mesh->vertices, i), delta_pos));
		i++;
	}
	j = 0;
	while (j < mesh->faces->size)
	{
		mesh_face = t_face_list_get(mesh->faces, j);
		//set_t_face_color(mesh_face, create_t_color(0.0, 1.0, 0.0, 1.0));
		triangle_mesh = compose_t_triangle_from_t_vertices(mesh->vertices_in_world, mesh_face->index_vertices);
		i = 0;
		while (i < target->faces->size)
		{
			target_face = t_face_list_get(target->faces, i);
			triangle_target = compose_t_triangle_from_t_vertices(target->vertices_in_world, target_face->index_vertices);
			if (is_triangle_in_triangle(triangle_mesh, triangle_target) == BOOL_TRUE)
			{
				set_t_face_color(mesh_face, create_t_color(1.0, 0.0, 0.0, 1.0));
				result++;
			}
			i++;
		}
		j++;
	}
	if (result > 0)
		return (BOOL_FALSE);
	return (BOOL_TRUE);
}

void			test_move_axis(t_mesh *mesh, float *force, t_vector3 axis, t_mesh *target)
{
	float	max;
	int		subdivision;
	int		i;
	float	delta;

	i = 0;
	subdivision = 10;
	delta = *force / subdivision;
	max = *force;
	*force = 0;

	while (i < subdivision && is_t_mesh_intersecting(mesh, target) == BOOL_FALSE)
	{
		i++;
		*force += delta;
		if (i == subdivision)
			*force = max;
		t_mesh_compute_next_vertices_in_world(mesh, axis);
		if (is_t_mesh_intersecting(mesh, target) == BOOL_TRUE)
			*force -= delta;
	}
}

int				can_move(t_mesh *mesh, t_mesh_list *mesh_list)
{
	t_mesh	*target;
	int		i;

	i = 0;
	while (i < mesh_list->size)
	{
		target = t_mesh_list_get(mesh_list, i);
		if (mesh != target && target->bubble_radius + mesh->bubble_radius >= calc_dist_vector3_to_vector3(mesh->center, target->center))
		{
			test_move_axis(mesh, &(mesh->force.x), create_t_vector3(1, 0, 0), target);
			test_move_axis(mesh, &(mesh->force.y), create_t_vector3(0, 1, 0), target);
			test_move_axis(mesh, &(mesh->force.z), create_t_vector3(0, 0, 1), target);
		}
		i++;
	}
	return (BOOL_TRUE);
}

void			t_physic_engine_compute_vertices_in_world(t_physic_engine *physic_engine)
{
	int i = 0;

	while (i < physic_engine->mesh_list->size)
	{
		t_mesh_compute_vertices_in_world(t_mesh_list_get(physic_engine->mesh_list, i));
		i++;
	}
}

void			t_physic_engine_apply_force(t_physic_engine *physic_engine)
{
	Uint32 	actual_frame;
	static Uint32 	last_frame = 0;
	int i = 0;
	float time_passed;
	t_mesh *mesh;

	actual_frame = SDL_GetTicks();
	time_passed = (actual_frame - last_frame) / 1000.0;
	while (i < physic_engine->mesh_list->size)
	{
		mesh = t_mesh_list_get(physic_engine->mesh_list, i);
		if (mesh->kinetic > 0)
			mesh->force = add_vector3_to_vector3(mesh->force, mult_vector3_by_float(physic_engine->gravity_force, mesh->kinetic * time_passed));
		if (mesh->force.x != 0 || mesh->force.y != 0 || mesh->force.z != 0)
			if (can_move(mesh, physic_engine->mesh_list) == BOOL_TRUE)
				t_mesh_apply_force(mesh);
		i++;

	}
	last_frame = actual_frame;
}
