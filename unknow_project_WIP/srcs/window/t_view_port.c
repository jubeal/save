#include "unknow_project.h"

t_view_port	create_t_view_port(t_window *p_window, t_vector2_int p_pos, t_vector2_int p_size)
{
	t_view_port	result;

	result.window = p_window;
	result.pos = create_t_vector2_int(0, 0);
	result.size = create_t_vector2_int(0, 0);


	if (!(result.depth_buffer = (float *)malloc(sizeof(float) * p_window->size_x * p_window->size_y)))
		error_exit(-456, "Can't malloc a float array properly");

	move_t_view_port(&result, p_pos);
	resize_t_view_port(&result, p_size);
	return (result);
}

t_view_port	*initialize_t_view_port(t_window *p_window, t_vector2_int p_pos, t_vector2_int p_size)
{
	t_view_port *result;

	if (!(result = (t_view_port *)malloc(sizeof(t_view_port))))
		return (NULL);

	*result = create_t_view_port(p_window, p_pos, p_size);

	return (result);
}

void		move_t_view_port(t_view_port *view, t_vector2_int new_pos)
{
	if (new_pos.x >= view->window->size_x - view->size.x)
		new_pos.x = view->window->size_x - view->size.x - 1;
	if (new_pos.y >= view->window->size_y - view->size.y)
		new_pos.y = view->window->size_y - view->size.y - 1;
	if (new_pos.x < 0)
		new_pos.x = 0;
	if (new_pos.y < 0)
		new_pos.y = 0;

	view->pos = new_pos;
}

void		resize_t_view_port(t_view_port *view, t_vector2_int new_size)
{
	if (new_size.x <= 0 || new_size.y <= 0)
		error_exit(325869, "size unavailable for t_view_port");
	if (view->pos.x + new_size.x >= view->window->size_x)
		new_size.x = view->window->size_x - view->pos.x - 1;
	if (view->pos.y + new_size.y >= view->window->size_y)
		new_size.y = view->window->size_y - view->pos.y - 1;

	view->size = new_size;
}

void		t_view_port_change_window(t_view_port *view, t_window *p_window)
{
	view->window = p_window;
	free(view->depth_buffer);
	if (!(view->depth_buffer = (float *)malloc(sizeof(float) * p_window->size_x * p_window->size_y)))
		error_exit(-456, "Can't malloc a float array properly");
	move_t_view_port(view, view->pos);
	resize_t_view_port(view, view->size);
}

void 		t_view_port_clear_buffers(t_view_port *view)
{
	for (int i = 0; i < view->window->size_x * view->window->size_y; i++)
	{
		view->depth_buffer[i] = INT_MAX;
	}
}