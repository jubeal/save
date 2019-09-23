#include "unknow_project.h"

t_gui create_t_gui(float x, int y)
{
	t_gui	result;
	int		idx;

	idx = 0;
	if (!(result.letter = (t_texture **)malloc(sizeof(t_texture*) * 95)))
		error_exit(-29, "Can't malloc a t_surface");
	while (idx <= 94)
	{
		if (!(result.letter[idx] = (t_texture *)malloc(sizeof(t_texture))))
			error_exit(-29, "Can't malloc a t_surface");
		if (!(result.letter[idx]->surface = (t_surface *)malloc(sizeof(t_surface))))
			error_exit(-29, "Can't malloc a t_surface");
		idx++;
	}
	idx = 0;
	if (!(result.menu = (t_texture **)malloc(sizeof(t_texture*) * 15)))
		error_exit(-29, "Can't malloc a t_surface");
	while (idx <= 14)
	{
		if (!(result.menu[idx] = (t_texture *)malloc(sizeof(t_texture))))
			error_exit(-29, "Can't malloc a t_surface");
		if (!(result.menu[idx]->surface = (t_surface *)malloc(sizeof(t_surface))))
			error_exit(-29, "Can't malloc a t_surface");
		idx++;
	}
	result.idx = 8;
	result.sens = 2;
	result.key_press = 0;
    result.perso.hp = x;
	result.perso.mun = y;
	return (result);
}

t_gui *initialize_t_gui(float x, int y)
{
	t_gui *result;

	if (!(result = (t_gui *)malloc(sizeof(t_gui))))
		error_exit(-13, "Can't create a t_gui");

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
	draw_buffer_opengl(main_camera->view_port->window, main_camera->view_port->window->color_data);
}

void	print_info_bar(t_camera *main_camera, t_gui *gui)
{
	char	*str;

	str = ft_itoa((int)(gui->perso.hp * 100));
	print_letter(main_camera, gui, ft_strcat(str, " / 100"), create_t_rectangle(create_t_vector2(-0.1, -0.92), create_t_vector2(0.02, 0.07)));
	str = ft_itoa(gui->perso.mun);
	print_letter(main_camera, gui, ft_strcat(str, " / 30"), create_t_rectangle(create_t_vector2(0.78, -0.90), create_t_vector2(0.01, 0.05)));
	free(str);
}
