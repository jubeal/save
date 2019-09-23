# include "unknow_project.h"

void            t_user_engine_handle_pause(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    if (*play == -1)
        main_pause(main_camera, gui, user_engine, play);
}

void            main_pause(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    print_letter(main_camera, gui, "RESUME", create_t_rectangle(create_t_vector2(-0.12, 0.14), create_t_vector2(0.04, 0.12)));
    print_letter(main_camera, gui, "MENU", create_t_rectangle(create_t_vector2(-0.08, -0.06), create_t_vector2(0.04, 0.12)));
    print_letter(main_camera, gui, "OPTION", create_t_rectangle(create_t_vector2(-0.12, -0.26), create_t_vector2(0.04, 0.12)));
    print_letter(main_camera, gui, "QUIT", create_t_rectangle(create_t_vector2(-0.08, -0.46), create_t_vector2(0.04, 0.12)));
}
