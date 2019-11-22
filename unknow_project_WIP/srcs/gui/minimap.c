#include "unknow_project.h"

void    draw_minimap(t_camera *main_camera, t_engine *engine, t_window *win)
{
    t_camera    *cam;

    t_engine_place_camera(engine, 1, add_vector4_to_vector4(t_camera_list_get(engine->visual_engine->camera_list, 0)->pos, create_t_vector4(0.0, 7.0, 0.0)));
	t_camera_look_at_point(t_camera_list_get(engine->visual_engine->camera_list, 1), t_camera_list_get(engine->visual_engine->camera_list, 0)->pos);
    cam = t_camera_list_get(engine->visual_engine->camera_list, 1);
    compute_t_camera(cam);
    draw_triangle_from_camera_on_screen(cam);

    t_engine_place_camera(engine, 2, t_camera_list_get(engine->visual_engine->camera_list, 2)->pos);
	t_camera_look_at_point(t_camera_list_get(engine->visual_engine->camera_list, 2), t_camera_list_get(engine->visual_engine->camera_list, 0)->pos);
    cam = t_camera_list_get(engine->visual_engine->camera_list, 2);
    compute_t_camera(cam);
    draw_triangle_from_camera_on_screen(cam);
}
