# include "unknow_project.h"

t_user_engine	create_t_user_engine()
{
	t_user_engine	result;

	result.mouse = initialize_t_mouse();
	result.keyboard = initialize_t_keyboard();

	return (result);
}

t_user_engine	*initialize_t_user_engine()
{
	t_user_engine	*result;

	if (!(result = (t_user_engine *)malloc(sizeof(t_user_engine))))
		return (NULL);
	// printf("malloc t_user_engine\n");

	*result = create_t_user_engine();

	return (result);
}

void			delete_t_user_engine(t_user_engine dest)
{
	free(dest.mouse);
	free(dest.keyboard);
	// printf("delete t_user_engine\n");
}

void			free_t_user_engine(t_user_engine *dest)
{
	delete_t_user_engine(*dest);
	free(dest);
	// printf("free t_user_engine\n");
}

void			t_user_engine_handle_camera(t_engine *engine, t_camera *cam, t_window *p_win)
{
	t_mouse *mouse = engine->user_engine->mouse;
	t_keyboard *keyboard = engine->user_engine->keyboard;
	get_t_mouse_info(mouse); // recuperation des informations mouse (position, et boutton utiliser)
	// if (mouse->pos.x != WIN_X / 2 && mouse->pos.y != WIN_Y / 2)
		handle_t_camera_view_by_mouse(cam, mouse); // calcul du mouvement de l'angle de la camera a la souris
	// if (mouse->pos.x == 0 || mouse->pos.x == WIN_X - 1 || mouse->pos.y == 0 || mouse->pos.y == WIN_Y - 1)
	// {
		SDL_WarpMouseInWindow(p_win->window, WIN_X / 2, WIN_Y / 2);
		// mouse->old_pos.x = WIN_X / 2;
		// mouse->old_pos.y = WIN_Y / 2;
		// print_t_vector2_int(mouse->rel_pos, "rel pos ");
	// }
	// else if (mouse->pos.x != WIN_X / 2 && mouse->pos.y != WIN_Y / 2)
		// handle_t_camera_view_by_mouse(cam, mouse);

	handle_t_camera_mouvement_by_key(cam, keyboard, engine); // deplacement cameras

	compute_t_camera(cam);
}

void			t_user_engine_handle_quit(t_user_engine *user_engine, int *play)
{
	if (get_key_state(user_engine->keyboard, SDL_SCANCODE_ESCAPE))
		*play = 0;
	if (user_engine->event.type == SDL_QUIT)
		*play = 0;
	if (user_engine->event.type == SDL_KEYDOWN && user_engine->event.key.keysym.sym == SDLK_ESCAPE)
		*play = 0;
}

int				t_user_engine_poll_event(t_user_engine *engine)
{
	return (SDL_PollEvent(&(engine->event)));
}
