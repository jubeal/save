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

void			free_t_physic_engine(t_physic_engine dest)
{
	delete_t_mesh_list(dest.mesh_list);
}

void			delete_t_physic_engine(t_physic_engine *dest)
{
	free_t_physic_engine(*dest);
	free(dest);
}

void			t_physic_engine_draw_mesh(t_physic_engine *p_physic_engine, t_window *p_win, t_camera *p_cam)
{
	int			i;

	i = 0;
	while (i < p_physic_engine->mesh_list->size)
	{
		draw_t_mesh(p_win, p_cam, t_mesh_list_get(p_physic_engine->mesh_list, i));
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

	return (BOOL_FALSE);
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
	}
}

int				can_move(t_mesh *mesh, t_mesh_list *mesh_list)
{
	t_mesh	*target;
	int		i;

	//printf("Delta %f - %f - %f\n", delta[0], delta[1], delta[2]);
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
