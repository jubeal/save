#ifndef UNKNOW_PROJECT_ENGINE_MODULE_H
# define UNKNOW_PROJECT_ENGINE_MODULE_H

# include "unknow_project_list.h"
# include "unknow_project_system.h"
# include "unknow_project_item.h"
# include "unknow_project_player.h"

typedef struct 	s_physic_engine
{
	t_mesh_list	*mesh_list;
	t_item_list	*item_list;
	t_vector4	gravity_force;
}				t_physic_engine;

t_physic_engine	create_t_physic_engine();
t_physic_engine	*initialize_t_physic_engine();
void			delete_t_physic_engine(t_physic_engine dest);
void			free_t_physic_engine(t_physic_engine *dest);

void			t_physic_engine_draw_mesh(t_physic_engine *p_physic_engine, t_camera *p_cam);
void			t_physic_engine_add_mesh(t_physic_engine *physic_engine, t_mesh p_mesh);
void			t_physic_engine_add_item(t_physic_engine *physic_engine, t_item p_item);
t_mesh			*t_physic_engine_get_mesh(t_physic_engine *physic_engine, int index);
void			t_physic_engine_compute_check_list(t_physic_engine *physic_engine);
int				calc_max_velocity(t_mesh *mesh, t_mesh *target, t_vector4 axis);

typedef struct	s_user_engine
{
	t_mouse		*mouse;
	t_keyboard	*keyboard;
	t_player	*player;
	SDL_Event	event;
}				t_user_engine;

t_user_engine	create_t_user_engine();
t_user_engine	*initialize_t_user_engine();
void			delete_t_user_engine(t_user_engine dest);
void			free_t_user_engine(t_user_engine *dest);

void			t_user_engine_handle_quit(t_user_engine *user_engine, int *play);
int				t_user_engine_poll_event(t_user_engine *engine);

typedef struct	s_visual_engine
{
	int			main_camera;
	t_camera_list
				*camera_list;
}				t_visual_engine;

t_visual_engine	create_t_visual_engine(t_window *p_window);
t_visual_engine	*initialize_t_visual_engine(t_window *p_window);
void			delete_t_visual_engine(t_visual_engine dest);
void			free_t_visual_engine(t_visual_engine *dest);
void			t_visual_engine_render_camera(t_visual_engine *engine);
void			t_visual_engine_prepare_camera(t_visual_engine *engine);
void			t_visual_engine_add_camera(t_visual_engine *engine, t_camera new_camera);
t_camera		*t_visual_engine_get_main_camera(t_visual_engine *engine);

#endif
