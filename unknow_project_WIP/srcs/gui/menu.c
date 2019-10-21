# include "unknow_project.h"

void            t_user_engine_handle_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    if (*play == 2)
        main_menu(main_camera, gui, user_engine, play);
    else if (*play == 3)
        option_menu(main_camera, gui, user_engine, play);
    else if (*play == 4)
        setting_menu(main_camera, gui, user_engine, play);
    else if (*play == 5)
        difficulty_menu(main_camera, gui, user_engine, play);
    else if (*play == 6)
        sens_menu(main_camera, gui, user_engine, play);
}

void			main_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
	t_mouse *mouse = user_engine->mouse;
	t_keyboard *keyboard = user_engine->keyboard;
	get_t_mouse_info(mouse);
	if (mouse->pos.x >= 35 && mouse->pos.x <= 270 && mouse->pos.y >= 410 && mouse->pos.y <= 560)
	{
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.9, 0.25), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.87, 0.22), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.84, 0.15), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.75, 0.25), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 1;
	}
	else if (mouse->pos.x >= 1580 && mouse->pos.x <= 1780 && mouse->pos.y >= 410 && mouse->pos.y <= 560)
	{
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.75, 0.25), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.84, 0.22), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.73, 0.15), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.92, 0.25), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 0;
	}
	else if (mouse->pos.x >= 35 && mouse->pos.x <= 345 && mouse->pos.y >= 870 && mouse->pos.y <= 1020)
	{
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.87, -0.56), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.69, -0.60), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.85, -0.46), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.78, -0.54), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.95, -0.62), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 0;
	}
	else if (mouse->pos.x >= 1490 && mouse->pos.x <= 1765 && mouse->pos.y >= 870 && mouse->pos.y <= 1020)
	{
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.76, -0.64), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.64, -0.52), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.80, -0.59), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.73, -0.48), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.90, -0.58), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 3;
	}
    else
        user_engine->mouse->clicked = BOOL_FALSE;
}

void			option_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
	t_mouse *mouse = user_engine->mouse;
	t_keyboard *keyboard = user_engine->keyboard;
	get_t_mouse_info(mouse);
    if (mouse->pos.x >= 350 && mouse->pos.x <= 670 && mouse->pos.y >= 450 && mouse->pos.y <= 555)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.30, 0.12), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.33, 0.18), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.47, 0.1), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.52, 0.15), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.4, 0.2), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.60, 0.13), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 4;
	}
    else if (mouse->pos.x >= 1135 && mouse->pos.x <= 1545 && mouse->pos.y >= 450 && mouse->pos.y <= 555)
    {
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.35, 0.16), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.52, 0.14), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.6, 0.15), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.46, 0.1), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.3, 0.08), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        if (t_mouse_state(mouse) == 2)
            *play = 5;
    }
	else if (mouse->pos.x >= 350 && mouse->pos.x <= 750 && mouse->pos.y >= 790 && mouse->pos.y <= 860)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.25, -0.38), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.33, -0.42), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.5, -0.39), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.6, -0.45), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.4, -0.46), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 6;
	}
	else if (mouse->pos.x >= 1150 && mouse->pos.x <= 1370 && mouse->pos.y >= 790 && mouse->pos.y <= 860)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.25, -0.39), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.35, -0.43), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.45, -0.37), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 0;
	}
	else if (mouse->pos.x >= 790 && mouse->pos.x <= 1050 && mouse->pos.y >= 1090 && mouse->pos.y <= 1160)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.14, -0.83), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.06, -0.88), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.11, -0.92), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.02, -0.85), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		if (t_mouse_state(mouse) == 2)
			*play = 2;
	}
    else
        user_engine->mouse->clicked = BOOL_FALSE;
}

void        setting_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    t_mouse *mouse = user_engine->mouse;
    t_keyboard *keyboard = user_engine->keyboard;

	get_t_mouse_info(mouse);
    if (gui->key_press != 2)
    {
        if (mouse->pos.x >= 320 && mouse->pos.x <= 630 && mouse->pos.y >= 395 && mouse->pos.y <= 440)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.74, 0.21), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_W;
                gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 320 && mouse->pos.x <= 660 && mouse->pos.y >= 510 && mouse->pos.y <= 560)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.74, 0.03), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_S;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 320 && mouse->pos.x <= 750 && mouse->pos.y >= 615 && mouse->pos.y <= 665)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.74, -0.15), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_A;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 320 && mouse->pos.x <= 795 && mouse->pos.y >= 725 && mouse->pos.y <= 780)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.74, -0.33), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_D;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 320 && mouse->pos.x <= 590 && mouse->pos.y >= 835 && mouse->pos.y <= 890)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.74, -0.51), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_LCTRL;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 320 && mouse->pos.x <= 490 && mouse->pos.y >= 945 && mouse->pos.y <= 1000)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.74, -0.69), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_SPACE;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 1080 && mouse->pos.x <= 1315 && mouse->pos.y >= 395 && mouse->pos.y <= 440)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.08, 0.21), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_LSHIFT;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 1080 && mouse->pos.x <= 1230 && mouse->pos.y >= 510 && mouse->pos.y <= 560)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.08, 0.03), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_A;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 1080 && mouse->pos.x <= 1615 && mouse->pos.y >= 615 && mouse->pos.y <= 665)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.08, -0.15), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_A;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 1080 && mouse->pos.x <= 1275 && mouse->pos.y >= 725 && mouse->pos.y <= 780)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.08, -0.33), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_A;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 1080 && mouse->pos.x <= 1330 && mouse->pos.y >= 835 && mouse->pos.y <= 890)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.08, -0.5), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_F;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 1080 && mouse->pos.x <= 1445 && mouse->pos.y >= 945 && mouse->pos.y <= 1000)
    	{
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.08, -0.69), create_t_vector2(0.1, 0.2)), gui->menu[12]);
    		if (t_mouse_state(mouse) == 2)
            {
                gui->key_change = SDL_SCANCODE_I;
    			gui->key_press = 2;
            }
    	}
        else if (mouse->pos.x >= 790 && mouse->pos.x <= 1050 && mouse->pos.y >= 1090 && mouse->pos.y <= 1160)
    	{
            draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.14, -0.83), create_t_vector2(0.05, 0.08)), gui->menu[7]);
            draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.06, -0.88), create_t_vector2(0.05, 0.08)), gui->menu[7]);
            draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.11, -0.92), create_t_vector2(0.05, 0.08)), gui->menu[7]);
    		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.02, -0.85), create_t_vector2(0.05, 0.08)), gui->menu[7]);
    		if (t_mouse_state(mouse) == 2)
    			*play = 3;
    	}
        else
            user_engine->mouse->clicked = BOOL_FALSE;
    }
    if (gui->key_press == 2)
    {
        set_controls(main_camera, gui, user_engine, gui->key_change);
    }
}

void        difficulty_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play)
{
    t_mouse *mouse = user_engine->mouse;
    t_keyboard *keyboard = user_engine->keyboard;
	get_t_mouse_info(mouse);
    if (mouse->pos.x >= 260 && mouse->pos.x <= 435 && mouse->pos.y >= 365 && mouse->pos.y <= 445)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[8]);
		if (t_mouse_state(mouse) == 2)
            gui->idx = 8;
	}
	else if (mouse->pos.x >= 260 && mouse->pos.x <= 495 && mouse->pos.y >= 540 && mouse->pos.y <= 610)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[9]);
		if (t_mouse_state(mouse) == 2)
            gui->idx = 9;
	}
	else if (mouse->pos.x >= 260 && mouse->pos.x <= 500 && mouse->pos.y >= 705 && mouse->pos.y <= 785)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[10]);
		if (t_mouse_state(mouse) == 2)
            gui->idx = 10;
	}
	else if (mouse->pos.x >= 260 && mouse->pos.x <= 600 && mouse->pos.y >= 885 && mouse->pos.y <= 950)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[11]);
		if (t_mouse_state(mouse) == 2)
            gui->idx = 11;
	}
    else if (mouse->pos.x >= 790 && mouse->pos.x <= 1050 && mouse->pos.y >= 1090 && mouse->pos.y <= 1160)
	{
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.14, -0.83), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(-0.06, -0.88), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.11, -0.92), create_t_vector2(0.05, 0.08)), gui->menu[7]);
		draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.02, -0.85), create_t_vector2(0.05, 0.08)), gui->menu[7]);
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[gui->idx]);
		if (t_mouse_state(mouse) == 2)
			*play = 3;
	}
    else
    {
        draw_rectangle_texture_cpu(main_camera->view_port, create_t_rectangle(create_t_vector2(0.1, -0.54), create_t_vector2(0.6, 0.94)), gui->menu[gui->idx]);
        user_engine->mouse->clicked = BOOL_FALSE;
    }
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
        user_engine->mouse->clicked = BOOL_FALSE;
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