#include "unknow_project.h"

t_keyboard	create_t_keyboard(void)
{
	t_keyboard	result;

	result.key[SDL_SCANCODE_W] = SDL_SCANCODE_W;
	result.key[SDL_SCANCODE_A] = SDL_SCANCODE_A;
	result.key[SDL_SCANCODE_S] = SDL_SCANCODE_S;
	result.key[SDL_SCANCODE_D] = SDL_SCANCODE_D;
	result.key[SDL_SCANCODE_F] = SDL_SCANCODE_F;
	result.key[SDL_SCANCODE_I] = SDL_SCANCODE_I;
	result.key[SDL_SCANCODE_LCTRL] = SDL_SCANCODE_LCTRL;
	result.key[SDL_SCANCODE_LSHIFT] = SDL_SCANCODE_LSHIFT;
	result.key[SDL_SCANCODE_SPACE] = SDL_SCANCODE_SPACE;
	result.state = SDL_GetKeyboardState(NULL);
	return (result);
}

t_keyboard	*initialize_t_keyboard(void)
{
	t_keyboard	*result;

	if (!(result = (t_keyboard *)malloc(sizeof(t_keyboard))))
		return (NULL);
	*result = create_t_keyboard();
	return (result);
}

int			get_key_state(t_keyboard *keyboard, int scan_code)
{
	if (keyboard->state[scan_code] != 0)
		return (1);
	return (0);
}

void		reset_key_state(t_keyboard *keyboard, int scan_code)
{
	((Uint8 *)(keyboard->state))[scan_code] = 0;
}
