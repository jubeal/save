#ifndef UNKNOW_PROJECT_ENGINE_H
# define UNKNOW_PROJECT_ENGINE_H

# include "unknow_project_camera.h"
# include "unknow_project_engine_module.h"

typedef struct	s_engine
{
	int			playing;

	t_visual_engine
				*visual_engine;
	t_physic_engine
				*physic_engine;
	t_user_engine
				*user_engine;
}				t_engine;

t_engine	create_t_engine(t_window *p_window);
t_engine	*initialize_t_engine(t_window *p_window);
void		delete_t_engine(t_engine dest);
void		free_t_engine(t_engine *dest);
void		t_engine_add_mesh(t_engine *engine, t_mesh p_mesh);
t_mesh		*t_engine_get_mesh(t_engine *p_engine, int index);

void		t_engine_handle_camera(t_engine *p_engine);
void		t_engine_draw_mesh(t_engine *p_engine);

// void		t_engine_handle_event(t_engine *engine);

void		t_engine_apply_physic(t_engine *engine);
void		t_engine_place_camera(t_engine *engine, int index, t_vector3 p_new_pos);
void		t_engine_camera_look_at(t_engine *engine, int index, t_vector3 target);

void		t_engine_render_camera(t_engine *engine);
void		t_engine_prepare_camera(t_engine *engine);

void		t_engine_add_camera(t_engine *p_engine, t_camera new_camera);

#endif