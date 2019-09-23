#include "unknow_project.h"

void		draw_pixel(t_window *p_win, int x, int y, t_color p_color)
{
	if (p_win->color_data[x + y * p_win->size_x].a != 0 && p_color.a != 1)
		p_color = fuze_t_color(p_color, p_win->color_data[x + y * p_win->size_x]);
	p_win->color_data[x + y * p_win->size_x] = p_color;
}
