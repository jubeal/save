# include "unknow_project.h"

void            t_user_engine_handle_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    if (*play == 2)
        main_menu(main_camera, gui, user_engine, play);
    if (*play == 3)
        settings_menu(main_camera, gui, user_engine, play);
    if (*play == 4)
        controls_menu(main_camera, gui, user_engine, play);
    if (*play == 5)
        credits_menu(main_camera, gui, user_engine, play);
    if (*play == -1)
        pause_menu(main_camera, gui, user_engine, play);
    if (*play == -2)
        settings_pause_menu(main_camera, gui, user_engine, play);
}

void			main_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
	t_mouse *mouse = user_engine->mouse;
	t_keyboard *keyboard = user_engine->keyboard;
    t_vector2_int pos;

	get_t_mouse_info(mouse);
    pos = create_t_vector2_int(mouse->pos.x * 100 / WIN_X, mouse->pos.y * 100 / WIN_Y);
    if (pos.x > 43 && pos.x < 56)
    {
        if (pos.y > 56 && pos.y < 61)
            if (t_mouse_state(mouse) == 2)
		        *play = 1;
        if (pos.y > 63 && pos.y < 68)
        	if (t_mouse_state(mouse) == 2)
		        *play = 3;
        if (pos.y > 70 && pos.y < 75)
        	if (t_mouse_state(mouse) == 2)
		        *play = 5;
        if (pos.y > 76 && pos.y < 82)
        	if (t_mouse_state(mouse) == 2)
		        *play = 0;
    }
    else
        user_engine->mouse->clicked_left = BOOL_FALSE;
}

void			pause_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
	t_mouse *mouse = user_engine->mouse;
	t_keyboard *keyboard = user_engine->keyboard;
    t_vector2_int pos;

	get_t_mouse_info(mouse);
    pos = create_t_vector2_int(mouse->pos.x * 100 / WIN_X, mouse->pos.y * 100 / WIN_Y);
    if (pos.x > 39 && pos.x < 61)
    {
        if (pos.y > 26 && pos.y < 32)
            if (t_mouse_state(mouse) == 2)
		        *play = 1;
        if (pos.y > 36 && pos.y < 41)
        	if (t_mouse_state(mouse) == 2)
		        *play = -2;
        if (pos.y > 45 && pos.y < 50)
        	if (t_mouse_state(mouse) == 2)
		        *play = 5;
        if (pos.y > 54 && pos.y < 59)
        	if (t_mouse_state(mouse) == 2)
		        *play = 2;
        if (pos.y > 64 && pos.y < 70)
        	if (t_mouse_state(mouse) == 2)
		        *play = 0;
    }
    else
        user_engine->mouse->clicked_left = BOOL_FALSE;
}

void			settings_pause_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
	t_mouse *mouse = user_engine->mouse;
	t_keyboard *keyboard = user_engine->keyboard;
    t_vector2_int pos;

	get_t_mouse_info(mouse);
    pos = create_t_vector2_int(mouse->pos.x * 100 / WIN_X, mouse->pos.y * 100 / WIN_Y);
    if (pos.x > 34 && pos.x < 64)
    {
        if (pos.y > 26 && pos.y < 32)
            if (t_mouse_state(mouse) == 2)
                printf("Mute\n");
        if (pos.y > 42 && pos.y < 46)
            if (t_mouse_state(mouse) == 2)
                printf("Sens +\n");
        if (pos.y > 55 && pos.y < 60)
            if (t_mouse_state(mouse) == 2)
                printf("Sens -\n");
        if (pos.y > 69 && pos.y < 75)
            if (t_mouse_state(mouse) == 2)
                *play = -1;
    }
    else
        user_engine->mouse->clicked_left = BOOL_FALSE;
}

void        settings_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{

    t_mouse *mouse = user_engine->mouse;
    t_keyboard *keyboard = user_engine->keyboard;
    t_vector2_int pos;

	get_t_mouse_info(mouse);
    pos = create_t_vector2_int(mouse->pos.x * 100 / WIN_X, mouse->pos.y * 100 / WIN_Y);
    printf("x = %d | y = %d\n", pos.x, pos.y);
    if (pos.x > 16 && pos.x < 29)
    {
        if (pos.y > 23 && pos.y < 26)
        	if (t_mouse_state(mouse) == 2)
		        printf("Mute master\n");
        if (pos.y > 27 && pos.y < 30)
        	if (t_mouse_state(mouse) == 2)
		        printf("Mute music\n");
        if (pos.y > 32 && pos.y < 35)
        	if (t_mouse_state(mouse) == 2)
		        printf("Mute sounds\n");
        if (pos.y > 44 && pos.y < 47)
        {
            draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[8]);
            if (t_mouse_state(mouse) == 2)
                gui->idx = 8;
        }
        if (pos.y > 48 && pos.y < 52)
        {
            draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[9]);
            if (t_mouse_state(mouse) == 2)
                gui->idx = 9;
        }
        if (pos.y > 53 && pos.y < 56)
        {
            draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[10]);
            if (t_mouse_state(mouse) == 2)
                gui->idx = 10;
        }
        if (pos.y > 72 && pos.y < 76)
            if (t_mouse_state(mouse) == 2)
                *play = 4;
    }
    else if (pos.x > 43 && pos.x < 56)
    {
        if (t_mouse_state(mouse) == 2)
            *play = 2;
    }
    else
        user_engine->mouse->clicked_left = BOOL_FALSE;
    // if (pos.y > 65 && pos.y < 69)
    // {
    //     if (pos.x == 17)
    //         if (t_mouse_state(mouse) == 2)
    //             gui->sens = 1;
    //     if (pos.x == 20)
    //         if (t_mouse_state(mouse) == 2)
    //             gui->sens = 2;
    //     if (pos.x == 24)
    //         if (t_mouse_state(mouse) == 2)
    //             gui->sens = 3;
    //     if (pos.x == 28)
    //         if (t_mouse_state(mouse) == 2)
    //             gui->sens = 4;
    //     if (pos.x == 31)
    //         if (t_mouse_state(mouse) == 2)
    //             gui->sens = 5;
    //     printf("Sensi = %d\n", gui->sens);
    // }
}

void        controls_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    t_mouse *mouse = user_engine->mouse;
    t_keyboard *keyboard = user_engine->keyboard;
    t_vector2_int pos;

	get_t_mouse_info(mouse);
    pos = create_t_vector2_int(mouse->pos.x * 100 / WIN_X, mouse->pos.y * 100 / WIN_Y);
    if (gui->key_press != 2)
    {
        if (pos.x > 23 && pos.x < 44)
        {
            if (pos.y > 28 && pos.y < 32)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_W;
                    gui->key_press = 2;
                }
            }
            else if (pos.y > 39 && pos.y < 44)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_S;
                    gui->key_press = 2;
                }
            }
            else if (pos.y > 51 && pos.y < 57)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_A;
                    gui->key_press = 2;
                }
            }
            else if (pos.y > 64 && pos.y < 69)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_D;
                    gui->key_press = 2;
                }
            }
            else
                user_engine->mouse->clicked_left = BOOL_FALSE;
        }
        if (pos.x > 64 && pos.x < 76)
        {
            if (pos.y > 28 && pos.y < 32)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_LCTRL;
                    gui->key_press = 2;
                }
            }
            else if (pos.y > 39 && pos.y < 44)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_SPACE;
                    gui->key_press = 2;
                }
            }
            else if (pos.y > 51 && pos.y < 57)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_LSHIFT;
                    gui->key_press = 2;
                }
            }
            else if (pos.y > 64 && pos.y < 69)
            {
                if (t_mouse_state(mouse) == 2)
                {
                    gui->key_change = SDL_SCANCODE_F;
                    gui->key_press = 2;
                }
            }
            else
                user_engine->mouse->clicked_left = BOOL_FALSE;
        }
    }
    if (gui->key_press == 2)
    {
        set_controls(main_camera, gui, user_engine, gui->key_change);
    }
    if (pos.x > 43 && pos.x < 56)
        if (pos.y > 82 && pos.y < 86)
            if (t_mouse_state(mouse) == 2)
                *play = 3;
}

void        sens_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    int i;
    t_mouse *mouse = user_engine->mouse;
    t_keyboard *keyboard = user_engine->keyboard;
	get_t_mouse_info(mouse);
    if (mouse->pos.x >= 420 && mouse->pos.x <= 620 && mouse->pos.y >= 635 && mouse->pos.y <= 835)
    {
        i = 1;
        sens_bis(main_camera, gui, i);
        if (t_mouse_state(mouse) == 2)
            gui->sens = 1;
    }
    else if (mouse->pos.x >= 620 && mouse->pos.x <= 820 && mouse->pos.y >= 635 && mouse->pos.y <= 835)
    {
        i = 2;
        sens_bis(main_camera, gui, i);
        if (t_mouse_state(mouse) == 2)
            gui->sens = 2;
    }
    else if (mouse->pos.x >= 820 && mouse->pos.x <= 1020 && mouse->pos.y >= 635 && mouse->pos.y <= 835)
    {
        i = 3;
        sens_bis(main_camera, gui, i);
        if (t_mouse_state(mouse) == 2)
            gui->sens = 3;
    }
    else if (mouse->pos.x >= 1020 && mouse->pos.x <= 1220 && mouse->pos.y >= 635 && mouse->pos.y <= 835)
    {
        i = 4;
        sens_bis(main_camera, gui, i);
        if (t_mouse_state(mouse) == 2)
            gui->sens = 4;
    }
    else if (mouse->pos.x >= 1220 && mouse->pos.x <= 1420 && mouse->pos.y >= 635 && mouse->pos.y <= 835)
    {
        i = 5;
        sens_bis(main_camera, gui, i);
        if (t_mouse_state(mouse) == 2)
            gui->sens = 5;
    }
    else if (mouse->pos.x >= 790 && mouse->pos.x <= 1050 && mouse->pos.y >= 1090 && mouse->pos.y <= 1160)
    {
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.14, -0.83), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.06, -0.88), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.11, -0.92), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.02, -0.85), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        sens_bis(main_camera, gui, gui->sens);
        if (t_mouse_state(mouse) == 2)
            *play = 3;
    }
    else
    {
        sens_bis(main_camera, gui, gui->sens);
        user_engine->mouse->clicked_left = BOOL_FALSE;
    }
}

void    sens_bis(t_camera *main_camera, t_gui *gui, int sens)
{
    int i;

    i = 0;
    while (i < sens)
    {
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.5825 + i * 0.2175, -0.43), create_t_vector2(0.3, 0.5)), gui->menu[13]);
        i++;
    }
}

void    set_controls(t_camera *main_camera, t_gui *gui, t_user_engine *engine, int key)
{
    int scan_code;
    draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-1, 1), create_t_vector2(2, -2)), gui->menu[14]);
    scan_code = engine->event.key.keysym.scancode;
    if (scan_code >= 4 && scan_code <= 231)
    {
        if (get_key_state(engine->keyboard, scan_code) == 1)
        {
            engine->keyboard->key[key] = scan_code;
            reset_key_state(engine->keyboard, scan_code);
            gui->key_press = 0;
        }
    }
}

void			credits_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
	t_mouse *mouse = user_engine->mouse;
	t_keyboard *keyboard = user_engine->keyboard;
    t_vector2_int pos;

	get_t_mouse_info(mouse);
    pos = create_t_vector2_int(mouse->pos.x * 100 / WIN_X, mouse->pos.y * 100 / WIN_Y);
    if (pos.x > 43 && pos.x < 56)
    {
        if (pos.y > 82 && pos.y < 86)
        	if (t_mouse_state(mouse) == 2)
		        *play = 2;
    }
    else
        user_engine->mouse->clicked_left = BOOL_FALSE;
}