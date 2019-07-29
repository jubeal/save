#include "unknow_project.h"

t_mouse			create_t_mouse()
{
	t_mouse		result;

	result.old_pos = create_t_vector2_int(-1, -1); //set de l'ancienne position a -1 (position pas encore regarder)
	result.pos = create_t_vector2_int(-1, -1); //set de la position actuelle a -1
	result.rel_pos = create_t_vector2_int(0, 0); //set de la position relative (difference entre old pos et new pos) a 0
	result.button[MOUSE_LEFT] = BOOL_FALSE; //initialisation du boutton en false (non clique)
	result.button[MOUSE_RIGHT] = BOOL_FALSE;
	result.button[MOUSE_MIDDLE] = BOOL_FALSE;

	return (result);
}

t_mouse			*initialize_t_mouse()
{
	t_mouse *result;

	if (!(result = (t_mouse *)malloc(sizeof(t_mouse))))
		return (NULL);

	*result = create_t_mouse();

	return (result);
}

void			get_t_mouse_info(t_mouse *mouse) //recuperation des informationd e la souris
{
	mouse->old_pos = mouse->pos;
	Uint32 mousestate = SDL_GetMouseState(&(mouse->pos.x), &(mouse->pos.y)); //recuperation de la position actuelle de la souris

	if (mouse->old_pos.x != -1)
		mouse->rel_pos = create_t_vector2_int((mouse->pos.x - mouse->old_pos.x), (mouse->pos.y - mouse->old_pos.y));
	if(mousestate & SDL_BUTTON(SDL_BUTTON_LEFT))
		mouse->button[MOUSE_LEFT] = BOOL_TRUE;
	else
		mouse->button[MOUSE_LEFT] = BOOL_FALSE;
	if(mousestate & SDL_BUTTON(SDL_BUTTON_RIGHT))
		mouse->button[MOUSE_RIGHT] = BOOL_TRUE;
	else
		mouse->button[MOUSE_RIGHT] = BOOL_FALSE;
	if(mousestate & SDL_BUTTON(SDL_BUTTON_MIDDLE))
		mouse->button[MOUSE_MIDDLE] = BOOL_TRUE;
	else
		mouse->button[MOUSE_MIDDLE] = BOOL_FALSE;

}

void			print_t_mouse(t_mouse *mouse) // affiche les infos de la souris
{
	char		*button_text[] = {
		"Mouse right",
		"Mouse left",
		"Mouse middle",
	};

	int i = 0;
	int find = 0;
	printf("[ %d][ %d ] - [ %d ][ %d ]", mouse->pos.x, mouse->pos.y, mouse->rel_pos.x, mouse->rel_pos.y);
	while (i < MOUSE_BUTTON)
	{
		if (mouse->button[i] == BOOL_TRUE)
		{
			printf("[%s]", button_text[i]);
			find++;
		}
		i++;
	}
	if (find == 0)
		printf("[NULL]");
	printf("\n");
}
