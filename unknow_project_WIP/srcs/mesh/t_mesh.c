#include "unknow_project.h"

t_mesh			create_t_mesh(t_vector3 pos)
{
	t_mesh result;

	result.pos = pos;
	result.is_visible = BOOL_TRUE;
	result.center = pos;
	result.bubble_radius = 0.0;

	result.force = create_t_vector3(0.0, 0.0, 0.0);
	result.kinetic = 0.0;

	result.angle = create_t_vector3(0.0, 90.0, 0.0);

	result.texture = NULL;

	result.vertices_in_world = initialize_t_vector3_list();
	result.next_vertices_in_world = initialize_t_vector3_list();

	result.vertices = initialize_t_vector3_list();
	result.uvs = initialize_t_vector3_list();
	result.faces = initialize_t_face_list();
	result.normales = initialize_t_vector3_list();

	t_mesh_look_at(&result);

	return (result);
}

t_mesh			*initialize_t_mesh(t_vector3 pos)
{
	t_mesh *result;

	if (!(result = (t_mesh *)malloc(sizeof(t_mesh))))
		error_exit(-13, "Can't create a t_mesh array");

	*result = create_t_mesh(pos);

	return(result);
}

void			free_t_mesh(t_mesh mesh)
{
	delete_t_vector3_list(mesh.vertices);
	delete_t_vector3_list(mesh.uvs);
	delete_t_face_list(mesh.faces);
}

void			delete_t_mesh(t_mesh *mesh)
{
	free_t_mesh(*mesh);
	free(mesh);
}

void			t_mesh_add_uv(t_mesh *dest, t_vector3 new_uv)
{
	t_vector3_list_push_back(dest->uvs, new_uv);
}

void			t_mesh_add_point(t_mesh *dest, t_vector3 new_point)
{
	t_vector3_list_push_back(dest->vertices, new_point);
}

void			t_mesh_add_face(t_mesh *dest, t_face new_face)
{
	t_face_list_push_back(dest->faces, new_face);
}

void 			t_mesh_set_texture(t_mesh *dest, t_texture *p_texture)
{
	dest->texture = p_texture;
}

void			t_mesh_compute_normals(t_mesh *mesh)
{
	t_face		*face;
	t_vector3	a;
	t_vector3	b;
	t_vector3	c;
	int			i;

	clean_t_vector3_list(mesh->normales);
	i = 0;
	while (i < mesh->faces->size)
	{
		face = t_face_list_get(mesh->faces, i);

		a = t_vector3_list_at(mesh->vertices, face->index_vertices[0]);
		b = substract_vector3_to_vector3(t_vector3_list_at(mesh->vertices, face->index_vertices[1]), a);
		c = substract_vector3_to_vector3(t_vector3_list_at(mesh->vertices, face->index_vertices[2]), a);

		face->normale = normalize_t_vector3(cross_t_vector3(b, c));

		t_vector3_list_push_back(mesh->normales, create_t_vector3(0, 0, 0));
		t_vector3_list_push_back(mesh->normales, face->normale);

		i++;
	}

}

void			t_mesh_compute_bubble_box(t_mesh *mesh)
{
	int			i = 0;
	float 		tmp;
	t_vector3	total;

	total = create_t_vector3(0.0, 0.0, 0.0);
	while (i < mesh->vertices->size)
	{
		total = add_vector3_to_vector3(total, t_vector3_list_at(mesh->vertices, i));
		i++;
	}
	if (i != 0)
		total = divide_vector3_by_float(total, (float)(i));
	mesh->center = add_vector3_to_vector3(total, mesh->pos);
	i = 0;
	while (i < mesh->vertices->size)
	{
		tmp = calc_dist_vector3_to_vector3(total, t_vector3_list_at(mesh->vertices, i));
		if (mesh->bubble_radius < tmp)
			mesh->bubble_radius = tmp;
		i++;
	}
}

void			t_mesh_look_at(t_mesh *mesh) // calcul de l'angle de vue du t_mesh (forward, right, up)
{
	t_vector3 zaxis = normalize_t_vector3(create_t_vector3(cos(degree_to_radius(mesh->angle.z)) * sin(degree_to_radius(mesh->angle.y)),
						sin(degree_to_radius(mesh->angle.z)),
						cos(degree_to_radius(mesh->angle.z)) * cos(degree_to_radius(mesh->angle.y))));
	t_vector3 xaxis = normalize_t_vector3(create_t_vector3(sin(degree_to_radius(mesh->angle.y) - 3.14f / 2.0f),
						0,
						cos(degree_to_radius(mesh->angle.y) - 3.14f / 2.0f)));
	t_vector3 yaxis = normalize_t_vector3(cross_t_vector3(xaxis, zaxis));

	mesh->forward = zaxis;
	mesh->right = xaxis;
	mesh->up = inv_t_vector3(yaxis);
}

void			t_mesh_rotate_around_point(t_mesh *mesh, t_vector3 delta_angle, t_vector3 center)
{
	t_matrix	translate;
	t_matrix	rotation;
	t_matrix	inv_translate;
	t_vector3	*target;

	translate = create_translation_matrix(substract_vector3_to_vector3(center, mesh->pos));
	inv_translate = create_translation_matrix(inv_t_vector3(substract_vector3_to_vector3(center, mesh->pos)));
	rotation = create_rotation_matrix(delta_angle.x, delta_angle.y, delta_angle.z);
	mesh->angle = add_vector3_to_vector3(mesh->angle, delta_angle);
	t_mesh_look_at(mesh);
	for (int i = 0; i < mesh->vertices->size; i++)
	{
		target = t_vector3_list_get(mesh->vertices, i);
		*target = mult_vector3_by_matrix(*target, inv_translate);
		*target = mult_vector3_by_matrix(*target, rotation);
		*target = mult_vector3_by_matrix(*target, translate);
	}
	t_mesh_compute_normals(mesh);
	t_mesh_compute_bubble_box(mesh);
}

void			t_mesh_rotate(t_mesh *mesh, t_vector3 delta_angle)
{
	t_matrix	rotation;
	t_vector3	*target;

	rotation = create_rotation_matrix(delta_angle.x, delta_angle.y, delta_angle.z);
	mesh->angle = add_vector3_to_vector3(mesh->angle, delta_angle);
	t_mesh_look_at(mesh);
	for (int i = 0; i < mesh->vertices->size; i++)
	{
		target = t_vector3_list_get(mesh->vertices, i);
		*target = mult_vector3_by_matrix(*target, rotation);
	}
	t_mesh_compute_normals(mesh);
	t_mesh_compute_bubble_box(mesh);
}

void 			t_mesh_set_color(t_mesh *dest, t_color p_color)
{
	int i = 0;
	while (i < dest->faces->size)
	{
		set_t_face_color(t_face_list_get(dest->faces, i), p_color);
		i++;
	}
}

void			t_mesh_move(t_mesh *dest, t_vector3 delta)
{
	dest->pos = add_vector3_to_vector3(dest->pos, delta);
	dest->center = add_vector3_to_vector3(dest->center, delta);
}

void			t_mesh_apply_force(t_mesh *dest)
{
	dest->pos = add_vector3_to_vector3(dest->pos, dest->force);
	dest->center = add_vector3_to_vector3(dest->center, dest->force);
}

void			t_mesh_set_force(t_mesh *dest, t_vector3 new_force)
{
	dest->force = new_force;
}

void			t_mesh_add_force(t_mesh *dest, t_vector3 delta_force)
{
	dest->force = add_vector3_to_vector3(dest->force, delta_force);
}

void			t_mesh_activate_gravity(t_mesh *dest, float gravity)
{
	dest->kinetic = gravity;
}

void			t_mesh_set_visibility(t_mesh *dest, int new_state)
{
	dest->is_visible = new_state;
}

void			t_mesh_compute_vertices_in_world(t_mesh *dest)
{
	t_face *dest_face;
	int i = 0;

	clean_t_vector3_list(dest->vertices_in_world);
	while (i < dest->vertices->size)
	{
		t_vector3_list_push_back(dest->vertices_in_world, add_vector3_to_vector3(t_vector3_list_at(dest->vertices, i), dest->pos));
		i++;
	}
}

void			t_mesh_compute_next_vertices_in_world(t_mesh *dest, t_vector3 axis)
{
	t_vector3 next_pos;
	t_face *dest_face;
	int i = 0;

	clean_t_vector3_list(dest->next_vertices_in_world);
	next_pos = add_vector3_to_vector3(dest->pos, mult_vector3_by_vector3(dest->force, axis));
	while (i < dest->vertices->size)
	{
		t_vector3_list_push_back(dest->next_vertices_in_world, add_vector3_to_vector3(t_vector3_list_at(dest->vertices, i), next_pos));
		i++;
	}
}