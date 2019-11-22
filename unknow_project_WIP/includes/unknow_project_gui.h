#ifndef UNKNOW_PROJECT_GUI_H
# define UNKNOW_PROJECT_GUI_H

# include "unknow_project_geometry.h"

typedef struct      s_button
{
    t_vector2_int   pos;
    t_vector2_int   size;
    char            clicked;
}                   t_button;

t_button            create_t_button();
t_button            *initialize_t_button();

int                 t_mouse_state(t_mouse *mouse);
int                 t_key_state(t_keyboard *key);

typedef struct  s_perso
{
    float       hp;
    int         mun;
}               t_perso;

typedef struct  s_gui
{
    t_perso     perso;
    t_texture   **letter;
    t_texture   **menu;
    int         idx;
    int         key_press;
    int         key_change;
    int         sens;
	int			info_print;
}               t_gui;

t_gui           create_t_gui(float x, int y);
t_gui           *initialize_t_gui(float x, int y);
void            drawing_front_hp(t_camera *main_camera, t_engine *engine);
void            drawing_front_mun(t_camera *main_camera, t_gui *gui, t_texture **texture, t_player *player);
void            draw_minimap(t_camera *main_camera, t_engine *engine, t_window *win);
void            load_letter(t_gui *gui, char *str, int idx);
void            set_t_gui_texte(t_gui *gui);
void            print_info_bar(t_camera *main_camera, t_player *player, t_gui *gui);
void            load_menu(t_gui *gui);
void            t_engine_handle_event(t_camera *main_camera, t_gui *gui, t_engine *engine);
void            t_user_engine_handle_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);

void            main_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            option_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            settings_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            controls_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            pause_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            settings_pause_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            credits_menu(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);
void            sens_bis(t_camera *main_camera, t_gui *gui, int sens);
void            set_controls(t_camera *main_camera, t_gui *gui, t_user_engine *engine, int key);

void            main_pause(t_camera *main_camera, t_gui *gui, t_user_engine *user_engine, int *play);

#endif
