#ifndef UNKNOW_PROJECT_H
# define UNKNOW_PROJECT_H

# include "unknow_project_includes.h"
# include "unknow_project_define.h"

# include "unknow_project_basic.h"
# include "unknow_project_math.h"
# include "unknow_project_drawing.h"
# include "unknow_project_system.h"
# include "unknow_project_engine.h"
# include "unknow_project_list.h"
# include "unknow_project_algorythm.h"
# include "unknow_project_gui.h"
# include "unknow_project_game_engine.h"
# include "unknow_project_player.h"
# include "unknow_project_item.h"

//			PNG reader
t_texture 		*png_load(char *path);

//			Shader - handler
GLuint			load_shaders(const char * p_vertex_file_path,
						const char * p_fragment_file_path);

//			convert
t_vector4		convert_screen_to_opengl(t_view_port *p_view_port, t_vector4 source);
t_vector2		convert_vector2_to_opengl(t_view_port *p_view_port, t_vector2 source);
t_vector4		convert_opengl_to_vector4(t_view_port *p_view_port, t_vector4 source);
t_vector2_int	convert_vector2_to_vector2_int(t_vector2 base);
t_vector4_int	convert_vector4_to_vector4_int(t_vector4 base);
t_vector4		convert_vector2_to_vector4(t_vector2 base);
float			degree_to_radius(float angle);
float			radius_to_degree(float radian);
t_uv 			convert_t_uv_to_texture(t_uv *source);

void			prepare_screen(t_window *win, t_color color);
void			check_frame(t_engine *engine);
void			render_screen(t_window *win, t_engine *engine);
void 			clear_buffers(t_window *win);
void			draw_pixel(t_window *p_win, int x, int y, t_color color);

t_triangle		compose_t_triangle_from_t_mesh(t_mesh *src, int *index);
t_triangle		compose_t_triangle_from_t_vertices(t_vector4_list *src, int *index);

#endif
