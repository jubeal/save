#include "unknow_project.h"

void    drawing_front_hp(t_camera *main_camera, t_engine *engine)
{
    static t_color    *color_back = NULL;
    static t_color    *color_hp = NULL;
    static t_color    *color_armor = NULL;
    static t_color    *color_jetpack = NULL;

    if (color_back == NULL && color_hp == NULL && color_armor == NULL)
    {
        color_back = initialize_t_color(0.7, 0.7, 0.7, 1.0);
        color_hp = initialize_t_color(1.0, 0.3, 0.3, 1.0);
        color_armor = initialize_t_color(0.3, 0.3, 1.0, 1.0);
        color_jetpack = initialize_t_color(1.0, 1.0, 0.3, 1.0);
    }
    t_view_port_clear_buffers(main_camera->view_port);
    draw_rectangle_color_cpu_front(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.22, -1), create_t_vector2(0.44, 0.22)), color_back);
    draw_rectangle_color_cpu_front(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.2, -0.98), create_t_vector2(0.4 * (float)(engine->user_engine->player->hp) / 100, 0.08)), color_hp);
    draw_rectangle_color_cpu_front(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.2, -0.88), create_t_vector2(0.4 * (float)(engine->user_engine->player->armor) / 100, 0.08)), color_armor);
    draw_rectangle_color_cpu_front(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.88, -0.88), create_t_vector2(0.2 * (float)(engine->user_engine->player->fuel) / 100, 0.08)), color_jetpack);
    draw_rectangle_color_cpu_front(main_camera->view_port, create_t_rectangle(create_t_vector2(0.0, 0.0), create_t_vector2(0.005, 0.01)), color_armor);
}

void    drawing_front_mun(t_camera *main_camera, t_gui *p_gui, t_texture **texture, t_player *player)
{
    int weapon;

    if (ft_strcmp(player->current_weapon->name, "pistol") == 0)
        weapon = 0;
    else if (ft_strcmp(player->current_weapon->name, "ar") == 0)
        weapon = 1;
    else if (ft_strcmp(player->current_weapon->name, "rifle") == 0)
        weapon = 2;
    else if (ft_strcmp(player->current_weapon->name, "shotgun") == 0)
        weapon = 3;
    t_view_port_clear_buffers(main_camera->view_port);
    draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.8, -1), create_t_vector2(0.2, 0.2)), texture[weapon]);
}
