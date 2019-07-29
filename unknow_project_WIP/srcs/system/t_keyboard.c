#include "unknow_project.h"

t_keyboard	create_t_keyboard()
{
	t_keyboard result;

	result.state = SDL_GetKeyboardState(NULL);

	return (result);
}

t_keyboard	*initialize_t_keyboard()
{
	t_keyboard *result;

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
