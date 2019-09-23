# include "unknow_project.h"

t_engine	create_t_engine(t_window *p_window)
{
	t_engine	result;

	result.playing = 2;
	result.visual_engine = initialize_t_visual_engine(p_window);
	result.physic_engine = initialize_t_physic_engine();
	result.user_engine = initialize_t_user_engine();

	return (result);
}

t_engine	*initialize_t_engine(t_window *p_window)
{
	t_engine	*result;

	if (!(result = (t_engine *)malloc(sizeof(t_engine))))
		return (NULL);

	*result = create_t_engine(p_window);

	return (result);
}

void		delete_t_engine(t_engine dest)
{
	free_t_physic_engine(dest.physic_engine);
	free_t_user_engine(dest.user_engine);
	free_t_visual_engine(dest.visual_engine);
}

void		free_t_engine(t_engine *dest)
{
	delete_t_engine(*dest);
	free(dest);
}

void		t_engine_handle_camera(t_engine *p_engine)
{
	t_user_engine_handle_camera(p_engine->user_engine,
								t_visual_engine_get_main_camera(p_engine->visual_engine),
								p_engine->physic_engine);
}

void		t_engine_draw_mesh(t_engine *p_engine)
{
	int i;

	i = 0;
	while (i < p_engine->visual_engine->camera_list->size)
	{
		t_physic_engine_draw_mesh(p_engine->physic_engine, t_camera_list_get(p_engine->visual_engine->camera_list, i));
		i++;
	}

}

void		t_engine_add_mesh(t_engine *engine, t_mesh p_mesh)
{
	t_physic_engine_add_mesh(engine->physic_engine, p_mesh);
}

void		t_engine_handle_event(t_camera *main_camera, t_gui *gui, t_engine *engine)
{
	static float size = 0.45;
	t_mesh	*mesh;
	int		i;

	if (engine->playing == 1 && get_key_state(engine->user_engine->keyboard, SDL_SCANCODE_P) == 1)
		engine->playing = -1;
	else if (engine->playing <= -1 && get_key_state(engine->user_engine->keyboard, SDL_SCANCODE_P) == 1)
		engine->playing = 1;
	t_user_engine_handle_pause(main_camera, gui, engine->user_engine, &(engine->playing));
	t_user_engine_handle_menu(main_camera, gui, engine->user_engine, &(engine->playing));
	if (t_user_engine_poll_event(engine->user_engine) > 0)
	{
		t_user_engine_handle_quit(engine->user_engine, &(engine->playing));
		if (engine->user_engine->event.type == SDL_KEYDOWN && engine->user_engine->event.key.keysym.sym == SDLK_u)
		{
			i = 0;
			while (i < engine->physic_engine->mesh_list->size)
			{
				mesh = t_mesh_list_get(engine->physic_engine->mesh_list, i);
				if (mesh->kinetic > 0)
					mesh->kinetic = 0;
				else
					mesh->kinetic = 100;
				i++;
			}
		}
	}
	// if (get_key_state(engine->user_engine->keyboard, SDL_SCANCODE_R) == 1)
	// {
	// 	printf("Size increased !\n");
	//
	// 	reset_key_state(engine->user_engine->keyboard, SDL_SCANCODE_R);
	// 	size += 0.2;
	// }
	// if (get_key_state(engine->user_engine->keyboard, SDL_SCANCODE_T) == 1)
	// {
	// 	size -= 0.2;
	// 	if (size <= 0.2)
	// 		size = 0.2;
	// 	printf("Size decreased !\n");
	//
	// 	reset_key_state(engine->user_engine->keyboard, SDL_SCANCODE_T);
	// }
}

t_mesh		*t_engine_get_mesh(t_engine *p_engine, int index)
{
	return (t_physic_engine_get_mesh(p_engine->physic_engine, index));
}

void		t_engine_apply_physic(t_engine *engine)
{
	t_physic_engine_compute_vertices_in_world(engine->physic_engine);
	t_physic_engine_apply_force(engine->physic_engine);
}

void		t_engine_place_camera(t_engine *engine, int index, t_vector3 p_new_pos)
{
	t_camera_list_get(engine->visual_engine->camera_list, index)->pos = p_new_pos;
}

void		t_engine_camera_look_at(t_engine *engine, int index, t_vector3 target)
{
	t_camera_look_at_point(t_camera_list_get(engine->visual_engine->camera_list, index), target);
	compute_t_camera(t_camera_list_get(engine->visual_engine->camera_list, index));
}

void		t_engine_render_camera(t_engine *engine)
{
	t_visual_engine_render_camera(engine->visual_engine);
}

void		t_engine_prepare_camera(t_engine *engine)
{
	t_visual_engine_prepare_camera(engine->visual_engine);
}

void		t_engine_add_camera(t_engine *p_engine, t_camera new_camera)
{
	t_visual_engine_add_camera(p_engine->visual_engine, new_camera);
}

int			t_engine_return_mesh_len(t_engine *engine)
{
	return (engine->physic_engine->mesh_list->size);
}