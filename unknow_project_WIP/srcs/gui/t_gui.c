#include "unknow_project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_gui create_t_gui(float x, int y)
{
	t_gui	result;
	int		idx;

	idx = 0;
	if (!(result.letter = (t_texture **)malloc(sizeof(t_texture*) * 95)))
		error_exit(-29, "Can't malloc a t_surface");
	// printf("malloc t_gui.letter\n");
	while (idx <= 94)
	{
		if (!(result.letter[idx] = (t_texture *)malloc(sizeof(t_texture))))
			error_exit(-29, "Can't malloc a t_surface");
		// printf("malloc t_gui.letter[idx]\n");
		if (!(result.letter[idx]->surface = (t_surface *)malloc(sizeof(t_surface))))
			error_exit(-29, "Can't malloc a t_surface");
		// printf("malloc t_gui.letter[idx]->surface\n");
		idx++;
	}
	idx = 0;
	if (!(result.menu = (t_texture **)malloc(sizeof(t_texture*) * 15)))
		error_exit(-29, "Can't malloc a t_surface");
	// printf("malloc t_gui.menu\n");
	while (idx <= 14)
	{
		if (!(result.menu[idx] = (t_texture *)malloc(sizeof(t_texture))))
			error_exit(-29, "Can't malloc a t_surface");
		// printf("malloc t_gui.menu[idx]\n");
		if (!(result.menu[idx]->surface = (t_surface *)malloc(sizeof(t_surface))))
			error_exit(-29, "Can't malloc a t_surface");
		// printf("malloc t_gui.menu[idx]->surface\n");
		idx++;
	}
	result.idx = 8;
	result.sens = 2;
	result.key_press = 0;
    result.perso.hp = x;
	result.perso.mun = y;
	result.info_print = 0;
	return (result);
}

t_gui *initialize_t_gui(float x, int y)
{
	t_gui *result;

	if (!(result = (t_gui *)malloc(sizeof(t_gui))))
		error_exit(-13, "Can't create a t_gui");

	// printf("malloc t_gui\n");
	*result = create_t_gui(x, y);

	return (result);
}

void	set_t_gui_texte(t_gui *gui)
{
	int 	i;
	char	letter;

	i = 32;
	letter = ' ';
	while (i <= 126)
	{
		load_letter(gui, &letter, i - 32);
		i++;
		letter++;
	}
}

void	print_letter(t_camera *main_camera, t_gui *gui, char *str, t_rectangle rec)
{
	int		i;
	int		idx;

	i = 0;
	t_view_port_clear_buffers(main_camera->view_port);
	while (i < ft_strlen(str))
	{
		idx = 0;
		while (idx <= 94)
		{
			if (str[i] == gui->letter[idx]->letter)
			{
			    draw_rectangle_texture_cpu(main_camera->view_port, rec, gui->letter[idx]);
				rec.pos = add_vector2_to_vector2(rec.pos, create_t_vector2(rec.size.x , 0.0));
				break ;
			}
			idx++;
		}
		i++;
	}
	// draw_buffer_opengl(main_camera->view_port->window, main_camera->view_port->window->color_data);
}

void	print_info_bar(t_camera *main_camera, t_player *player, t_gui *gui)
{
	char		*str;

	str = ft_itoa(player->armor);
	print_letter(main_camera, gui, ft_strcat(str, "%"), create_t_rectangle(create_t_vector2(-0.025, -0.87), create_t_vector2(0.02, 0.07)));
	free(str);
	str = ft_itoa(player->hp);
	print_letter(main_camera, gui, ft_strcat(str, "%"), create_t_rectangle(create_t_vector2(-0.025, -0.97), create_t_vector2(0.02, 0.07)));
	free(str);

	str = ft_itoa(player->current_weapon->ammo);
	str = ft_strjoinf(str, " / ", 1);
	str = ft_strjoinf(str, ft_itoa(player->current_weapon->total_ammo), 3);

	print_letter(main_camera, gui, str, create_t_rectangle(create_t_vector2(0.78, -0.90), create_t_vector2(0.01, 0.05)));
	free(str);
}
