#include "unknow_project.h"

void			test_move_axis_bis(t_mesh *mesh, float *force, t_vector4 axis, t_mesh *target)
{
	float	max;
	int		subdivision;
	int		i;
	float	delta;

	if (force == NULL)
		error_exit(1, "Force = NULL");
	if (mesh == NULL)
		error_exit(1, "mesh = NULL");
	if (target == NULL)
		error_exit(1, "target = NULL");

	i = 0;
	subdivision = 20;
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
		{
			*force -= delta;
			if (ft_strcmp(target->name, "ladder") == 0)
				mesh->force.y = 0.02;
		}
	}
}

int				can_move_bis(t_mesh *mesh, t_engine *engine, char *name)
{
	t_mesh	*target;
	int		i;
	int		j;

	i = 0;
	while (i < engine->physic_engine->mesh_list->size)
	{
		target = t_mesh_list_get(engine->physic_engine->mesh_list, i);
		if (mesh != target && target->bubble_radius + mesh->bubble_radius >= calc_dist_vector4_to_vector4(mesh->center, target->center) && target->no_hitbox == 0 && ft_strcmp(target->name, name) != 0)
		{
			test_move_axis_bis(mesh, &(mesh->force.y), create_t_vector4(0, 1, 0), target);
			test_move_axis_bis(mesh, &(mesh->force.x), create_t_vector4(1, 0, 0), target);
			test_move_axis_bis(mesh, &(mesh->force.z), create_t_vector4(0, 0, 1), target);
		}
		i++;
	}
	return (BOOL_TRUE);
}

void	cast_mesh(t_engine *engine, t_mesh *mesh_editing, char *name)
{
	t_camera	*cam;

	cam = t_camera_list_get(engine->visual_engine->camera_list, 0);
	mesh_editing->force = cam->forward;
	while (mesh_editing->force.x != 0 && mesh_editing->force.y != 0 && mesh_editing->force.z != 0)
	{
		if ((mesh_editing->pos.x - cam->pos.x > 10 || mesh_editing->pos.x - cam->pos.x < -10)
			|| (mesh_editing->pos.y - cam->pos.y > 10 || mesh_editing->pos.y - cam->pos.y < -10)
			||	(mesh_editing->pos.z - cam->pos.z > 10 || mesh_editing->pos.z - cam->pos.z < -10))
			mesh_editing->force = create_t_vector4(0.0, 0.0, 0.0);
		if (can_move_bis(mesh_editing, engine, name) == BOOL_TRUE)
			t_mesh_move(mesh_editing, mesh_editing->force);
	}
	mesh_editing->force = create_t_vector4(0.0, 0.0, 0.0);
}
