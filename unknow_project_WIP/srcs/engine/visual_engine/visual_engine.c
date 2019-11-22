#include "unknow_project.h"

t_visual_engine	create_t_visual_engine(t_window *p_window)
{
	t_visual_engine	result;
	t_camera tmp;

	result.camera_list = initialize_t_camera_list();
	result.main_camera = 0;
	tmp = create_t_camera(p_window, create_t_vector4(0, 0, 0), FOV, create_t_vector2(NEAR, FAR));
	t_camera_list_push_back(result.camera_list, tmp);

	return (result);
}

t_visual_engine	*initialize_t_visual_engine(t_window *p_window)
{
	t_visual_engine	*result;

	if (!(result = (t_visual_engine *)malloc(sizeof(t_visual_engine))))
		return (NULL);
	// printf("malloc t_visual_engine\n");

	*result = create_t_visual_engine(p_window);

	return (result);
}

void			delete_t_visual_engine(t_visual_engine dest)
{
	free_t_camera_list(dest.camera_list);
	// printf("delete t_visual_engine\n");
}

void			free_t_visual_engine(t_visual_engine *dest)
{
	delete_t_visual_engine(*dest);
	free(dest);
	// printf("free t_visual_engine\n");
}

void			t_visual_engine_render_camera(t_visual_engine *engine)
{
	int			i;

	i = 0;
	while (i < engine->camera_list->size)
	{
		t_camera *cam = t_camera_list_get(engine->camera_list, i);
		compute_t_camera(cam);
		draw_triangle_from_camera_on_screen(cam);
		i++;
	}
}

void			t_visual_engine_render_first_camera(t_visual_engine *engine)
{
	t_camera *cam = t_camera_list_get(engine->camera_list, 0);
	compute_t_camera(cam);
	draw_triangle_from_camera_on_screen(cam);
}

void			t_visual_engine_prepare_camera(t_visual_engine *engine)
{
	int			i;

	i = 0;
	while (i < engine->camera_list->size)
	{
		clean_t_camera(t_camera_list_get(engine->camera_list, i));
		i++;
	}
}

void			t_visual_engine_add_camera(t_visual_engine *engine, t_camera new_camera)
{
	t_camera_list_push_back(engine->camera_list, new_camera);
}

t_camera		*t_visual_engine_get_main_camera(t_visual_engine *engine)
{
	t_camera *result;

	result = t_camera_list_get(engine->camera_list, engine->main_camera);

	return (result);
}
