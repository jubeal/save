#include "unknow_project.h"

t_camera	create_t_camera(t_window *window, t_vector3 p_pos, float p_fov, t_vector2 p_dist)
{
	t_camera result;

	result.view_port = initialize_t_view_port(window, create_t_vector2_int(0, 0), create_t_vector2_int(window->size_x, window->size_y));

	result.body = NULL;
	result.pos = p_pos; //position de la camera
	result.fov = p_fov; // champ de vision
	result.near = p_dist.x; //distance la plus proche pour voir un objet
	result.far = p_dist.y; // distance la plus eloigne pour voir un objet
	result.yaw = 0; // angle a laquel on voit l'objet
	result.pitch = 0; // angle a laquel on voit l'objet
	result.speed = 0.1f; // vitesse de deplacement
	result.running = 1.8f; // action de courir
	result.slowing = 1.0f; // ralentissement pour le recul
	result.crounch = 0;
	result.f_press = 0;

	result.model = create_t_matrix(); // creation de la matrice d'identite permettant de faire les calculs matriciel par la suite
	t_camera_look_at(&result); //calcul de l'angle de la camera
	result.view = t_camera_compute_view(&result); //calcul de la matrice de vue
	result.projection = compute_projection_matrix(&result); //calcul de la matrice de projection
	result.sun_direction = normalize_t_vector3(create_t_vector3(0.2, -1, -0.4)); // direction de la lumiere
	result.triangle_color_list = create_t_triangle_list(); // list des triangles
	result.color_list = create_t_color_list(); //list des couleurs

	result.triangle_texture_list = create_t_triangle_list();
	result.uv_list = create_t_uv_list();
	result.darkness_list = create_t_color_list();

	return (result);
}

t_camera	*initialize_t_camera(t_window *window, t_vector3 p_pos, float p_fov, t_vector2 p_dist)
{
	t_camera *result;

	if (!(result = (t_camera *)malloc(sizeof(t_camera))))
		error_exit(-31, "Can't malloc a t_camera");
	// printf("malloc t_camera\n");

	*result = create_t_camera(window, p_pos, p_fov, p_dist);

	return (result);
}

void		t_camera_set_view_port(t_camera *camera, t_vector2_int new_pos, t_vector2_int new_size)
{
	move_t_view_port(camera->view_port, new_pos);
	resize_t_view_port(camera->view_port, new_size);
}

void		t_camera_change_window(t_camera *camera, t_window *new_window)
{
	t_view_port_change_window(camera->view_port, new_window);
}

void		t_camera_change_view_port(t_camera *camera, t_view_port *new_view_port)
{
	free(camera->view_port);
	camera->view_port = new_view_port;
	// printf("free change_t_camera\n");
}

void		delete_t_cam(t_camera dest)
{
	delete_t_triangle_list(dest.triangle_color_list);
	delete_t_color_list(dest.color_list);
	delete_t_triangle_list(dest.triangle_texture_list);
	delete_t_uv_list(dest.uv_list);
	delete_t_color_list(dest.darkness_list);
	free(dest.view_port);
	// printf("delete t_camera\n");
}

void		free_t_cam(t_camera *dest)
{
	delete_t_cam(*dest);
	free(dest);
	// printf("free t_camera\n");
}

void		t_camera_look_at_point(t_camera *cam, t_vector3 target) // calcul de l'angle de vue de la camera (forward, right, up)
{
	if (target.x == cam->pos.x && target.y == cam->pos.y && target.z == cam->pos.z)
		return ;

	t_vector3 result = normalize_t_vector3(substract_vector3_to_vector3(cam->pos, target));

	cam->yaw = radius_to_degree(atan2(result.z, -result.x)) - 90;
	cam->pitch = radius_to_degree(atan2(result.y, sqrt(result.x * result.x + result.z * result.z)));
	cam->pitch = clamp_float_value(-89, cam->pitch, 89);

	t_camera_look_at(cam);
}

void		t_camera_look_at(t_camera *cam) // calcul de l'angle de vue de la camera (forward, right, up)
{
	t_vector3 zaxis = normalize_t_vector3(create_t_vector3(cos(degree_to_radius(cam->pitch)) * sin(degree_to_radius(cam->yaw)),
						sin(degree_to_radius(cam->pitch)),
						cos(degree_to_radius(cam->pitch)) * cos(degree_to_radius(cam->yaw))));
	t_vector3 xaxis = normalize_t_vector3(create_t_vector3(sin(degree_to_radius(cam->yaw) - 3.14f / 2.0f),
						0,
						cos(degree_to_radius(cam->yaw) - 3.14f / 2.0f)));
	t_vector3 yaxis = normalize_t_vector3(cross_t_vector3(xaxis, zaxis));

	cam->forward = inv_t_vector3(zaxis);
	cam->right = xaxis;
	cam->up = inv_t_vector3(yaxis);
}

t_matrix	t_camera_compute_view(t_camera *cam) //calcul de la matrice de vue
{
	t_matrix	result;

	result = create_t_matrix();

	result.value[0][0] = cam->right.x;
	result.value[1][0] = cam->right.y;
	result.value[2][0] = cam->right.z;
	result.value[3][0] = - (dot_t_vector3(cam->right, cam->pos));

	result.value[0][1] = cam->up.x;
	result.value[1][1] = cam->up.y;
	result.value[2][1] = cam->up.z;
	result.value[3][1] = - (dot_t_vector3(cam->up, cam->pos));

	result.value[0][2] = cam->forward.x;
	result.value[1][2] = cam->forward.y;
	result.value[2][2] = cam->forward.z;
	result.value[3][2] = -(dot_t_vector3(cam->forward, cam->pos));

	return (result);
}

void		t_camera_change_fov(t_camera *cam, float delta)
{
	if (delta > 1 && cam->fov >= 60)
		cam->fov /= delta;
	if (delta < 1 && cam->fov < 90)
		cam->fov /= delta;
}

t_matrix	compute_projection_matrix(t_camera *p_cam) //calcul de la matrice de projection
{
	t_matrix	result;
	float		n;
	float		r;
	float		f;
	float		t;

	result = create_t_matrix_empty();
	n = p_cam->near;
	r = 1.0 / (tan(degree_to_radius(p_cam->fov / 2.0)));
	f = p_cam->far;
	t = 1.0 / (tan(degree_to_radius(p_cam->fov / 2.0))) / (4.0 / 3.0); // changer le (4/3) en (16/9) va changer le ratio de l'ecran, changeant l'apparence des cubes a l'ecran
	result.value[0][0] = t;
	result.value[1][1] = r;
	result.value[2][2] = -(f) / (f - n);
	result.value[2][3] = -1.0;
	result.value[3][2] = -(2.0 * f * n) / (f - n);
	return (result);
}

void		compute_t_camera(t_camera *cam)
{
	cam->view = t_camera_compute_view(cam);
	cam->projection = compute_projection_matrix(cam);
}

t_vector3	apply_t_camera(t_vector3 *src, t_matrix *mat) // applique la position de la camera
{
	t_vector3	result; // x -> coord a l'ecran en x de ce point / y -> coord a l'ecran en y de ce point / z -> distance reelle entre ce point et l'oeil de la camera
	float		delta;

	result.x = src->x * mat->value[0][0] + src->y * mat->value[1][0] + src->z * mat->value[2][0] + mat->value[3][0];
	result.y = src->x * mat->value[0][1] + src->y * mat->value[1][1] + src->z * mat->value[2][1] + mat->value[3][1];
	result.z = src->x * mat->value[0][2] + src->y * mat->value[1][2] + src->z * mat->value[2][2] + mat->value[3][2];
	delta = src->x * mat->value[0][3] + src->y * mat->value[1][3] + src->z * mat->value[2][3] + mat->value[3][3];
	if (delta != 0)
	{
		result.x /= delta;
		result.y /= delta;
		result.z /= -delta;
	}
	//result.z = calc_dist_vector3_to_vector3(create_t_vector3(0, 0, 0), *src);
	return (result);
}

void		t_camera_change_view(t_camera *cam, float delta_pitch, float delta_yaw)
{
	cam->pitch = clamp_float_value(-89, cam->pitch + delta_pitch , 89);
	cam->yaw += delta_yaw;
	t_camera_look_at(cam);
}

void		move_camera(t_camera *camera, t_vector3 mouvement, t_engine *engine, float j)
{
	if (can_move(camera->body, engine) == BOOL_TRUE)
		t_mesh_move(camera->body, camera->body->force);
	t_physic_engine_apply_force(engine);
	camera->pos = add_vector3_to_vector3(camera->pos, camera->body->force);
	camera->pos = add_vector3_to_vector3(camera->body->pos,
					create_t_vector3(0.15, 0.45 - j, 0.15));
}

void		handle_t_camera_mouvement_by_key(t_camera *camera, t_keyboard *p_keyboard, t_engine *engine) // calcul du mouvement de la cameraera au clavier
{
	static t_mesh	*door = NULL;
	t_mesh			*target;
	t_vector3		tmp;
	t_vector3		mouvement;
	t_vector3		save;
	float			y;
	float			j;
	int				i;
	int				k;
	int				l;

	j = 0.0;
	i = 0;
	mouvement = create_t_vector3(0, 0, 0);
	save = create_t_vector3(0, 0, 0);
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_SPACE]) == 1 && camera->body->force.y == 0)
	{
		camera->body->force.y = 0.05;
	}
	y = camera->body->force.y;
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_LSHIFT]) == 1 && camera->body->force.y == 0)
		tmp = create_t_vector3(camera->speed * camera->running, 0.0, camera->speed * camera->running);
	else
		tmp = create_t_vector3(camera->speed, 0.0, camera->speed);
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_S]) == 1)
	{
		tmp = create_t_vector3(camera->speed / camera->slowing, 0.0, camera->speed / camera->slowing);
		camera->body->force = add_vector3_to_vector3(mult_vector3_by_vector3(normalize_t_vector3(mult_vector3_by_vector3(camera->forward, create_t_vector3(-1.0, 0.0, -1.0))), tmp), mouvement);
		save = create_t_vector3(camera->body->force.x, 0, camera->body->force.z);
	}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_W]) == 1)
	{
		camera->body->force = add_vector3_to_vector3(mult_vector3_by_vector3(normalize_t_vector3(mult_vector3_by_vector3(camera->forward, create_t_vector3(1.0, 0.0, 1.0))), tmp), mouvement);
		if (save.x != 0 || save.y != 0 || save.z != 0)
			save = add_vector3_to_vector3(divide_vector3_by_float(camera->body->force, 2), divide_vector3_by_float(save, 2));
		else
			save = create_t_vector3(camera->body->force.x, 0, camera->body->force.z);
	}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_D]) == 1)
	{
		camera->body->force = add_vector3_to_vector3(mult_vector3_by_vector3(inv_t_vector3(camera->right), tmp), mouvement);
		if (save.x != 0 || save.y != 0 || save.z != 0)
			save = add_vector3_to_vector3(divide_vector3_by_float(camera->body->force, 2), divide_vector3_by_float(save, 2));
		else
			save = create_t_vector3(camera->body->force.x, 0, camera->body->force.z);
}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_A]) == 1)
	{
		camera->body->force = add_vector3_to_vector3(mult_vector3_by_vector3(camera->right, tmp), mouvement);
		if (save.x != 0 || save.y != 0 || save.z != 0)
			save = add_vector3_to_vector3(divide_vector3_by_float(camera->body->force, 2), divide_vector3_by_float(save, 2));
		else
			save = create_t_vector3(camera->body->force.x, 0, camera->body->force.z);
	}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_LCTRL]) == 1)
	{
		j = 0.2;
		if (camera->crounch == 0)
		{
			t_mesh_resize(camera->body, create_t_vector3(0.0, -0.2, 0.0));
			camera->crounch = 1;
		}
	}
	else if (camera->crounch == 1)
	{
		k = 0;
		l = 0;
		while (i < engine->physic_engine->mesh_list->size)
		{
			target = t_mesh_list_get(engine->physic_engine->mesh_list, i);
			if (camera->body != target && target->bubble_radius + camera->body->bubble_radius >= calc_dist_vector3_to_vector3(camera->body->center, target->center))
			{
				k++;
				if (camera->body->pos.y > target->pos.y || target->pos.y - camera->body->pos.y >= 0.49)
					l++;
			}
			i++;
		}
		if (k == l)
		{
			t_mesh_resize(camera->body, create_t_vector3(0.0, 0.2, 0.0));
			camera->crounch = 0;
			j = 0.0;
		}
		else
			j = 0.2;
	}
	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_F]) == 1)
	{
		i = 0;
		while(i < engine->physic_engine->mesh_list->size && camera->f_press == 0)
		{
			target = t_mesh_list_get(engine->physic_engine->mesh_list, i);
			if (camera->body != target && target->bubble_radius + camera->body->bubble_radius >= calc_dist_vector3_to_vector3(camera->body->center, target->center) && ft_strcmp(target->name, "door") == 0)
			{
				target->door.move = 1;
				door = target;
			}
			i++;
		}
		camera->f_press = 1;
	}
	else
		camera->f_press = 0;

	if (get_key_state(p_keyboard, p_keyboard->key[SDL_SCANCODE_B]) == 1)
	{
		save_map(engine->physic_engine->mesh_list, 1);
	}

	if (door != NULL)
		t_mesh_move_door(door);
	camera->body->force = create_t_vector3(save.x, y, save.z);
	move_camera(camera, camera->body->force, engine, j);
	camera->body->force = mult_vector3_by_vector3(camera->body->force, create_t_vector3(0.0, 1.0, 0.0));
}

void		handle_t_camera_view_by_mouse(t_camera *cam, t_mouse *p_mouse) // calcul du mouvement de l'angle de la camera a la souris
{
	float delta_pitch;
	float delta_yaw;

	delta_pitch = -(p_mouse->rel_pos.x / 10.0);
	delta_yaw = p_mouse->rel_pos.y / 10.0;
	t_camera_change_view(cam, delta_yaw, delta_pitch);
}

void 		t_camera_calc_depth(t_camera *p_cam)
{
	t_triangle	triangle;
	int			i;

	p_cam->dist_max = 0.0f;
	i = 0;
	while (i < p_cam->triangle_color_list.size)
	{
		triangle = t_triangle_list_at(&(p_cam->triangle_color_list), i);
		if (triangle.a.z > p_cam->dist_max)
			p_cam->dist_max = triangle.a.z;
		else if (triangle.b.z > p_cam->dist_max)
			p_cam->dist_max = triangle.b.z;
		else if (triangle.c.z > p_cam->dist_max)
			p_cam->dist_max = triangle.c.z;
		i++;
	}
	i = 0;
	while (i < p_cam->triangle_texture_list.size)
	{
		triangle = t_triangle_list_at(&(p_cam->triangle_texture_list), i);
		if (triangle.a.z > p_cam->dist_max)
			p_cam->dist_max = triangle.a.z;
		else if (triangle.b.z > p_cam->dist_max)
			p_cam->dist_max = triangle.b.z;
		else if (triangle.c.z > p_cam->dist_max)
			p_cam->dist_max = triangle.c.z;
		i++;
	}
}

void		draw_depth_from_camera_on_screen(t_camera *p_cam)
{
	t_triangle	triangle;
	t_line		line1;
	t_line		line2;
	int			i;

	t_camera_calc_depth(p_cam);
	i = 0;
	while (i < p_cam->triangle_color_list.size)
	{
		triangle = t_triangle_list_at(&(p_cam->triangle_color_list), i);
		draw_triangle_depth_cpu(p_cam->view_port, &triangle, p_cam->dist_max);
		i++;
	}
	i = 0;
	while (i < p_cam->triangle_texture_list.size)
	{
		triangle = t_triangle_list_at(&(p_cam->triangle_texture_list), i);
		draw_triangle_depth_cpu(p_cam->view_port, &triangle, p_cam->dist_max);
		i++;
	}
}

void		draw_triangle_from_camera_on_screen(t_camera *p_cam)
{
	if (p_cam->triangle_color_list.size > 0)
		multithreading_draw_triangle_color_cpu(p_cam->view_port, &(p_cam->triangle_color_list), &(p_cam->color_list));
	if (p_cam->triangle_texture_list.size > 0)
		multithreading_draw_triangle_texture_cpu(p_cam->view_port, &(p_cam->triangle_texture_list), &(p_cam->uv_list));
}

void		clean_t_camera(t_camera *camera)
{
	clean_t_triangle_list(&(camera->triangle_color_list));
	clean_t_color_list(&(camera->color_list));
	clean_t_triangle_list(&(camera->triangle_texture_list));
	clean_t_color_list(&(camera->darkness_list));
	clean_t_uv_list(&(camera->uv_list));
	t_view_port_clear_buffers(camera->view_port);
}

void		link_t_camera_to_t_mesh(t_camera *camera, t_mesh *mesh, float new_kinetic)
{
	if (camera->body != NULL)
		camera->body->camera = NULL;
	camera->body = mesh;
	if (mesh != NULL)
	{
		camera->body->kinetic = new_kinetic;
		mesh->camera = camera;
	}
}
