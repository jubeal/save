#ifndef UNKNOW_PROJECT_MESH_H
# define UNKNOW_PROJECT_MESH_H

# include "unknow_project_basic_list.h"
# include "unknow_project_window.h"

typedef struct		s_door
{
	int				tick;
	int				state;
	int				move;
}					t_door;

t_door			create_t_door(void);
t_door			*initialize_t_door(void);

typedef struct		s_mesh
{
	struct s_camera	*camera;
	t_vector3		pos;
	t_vector3		size;
	t_vector3		center;
	int				is_visible;
	int				no_hitbox;
	float			bubble_radius;
	int				collectible; // 0 false 1 true

	t_vector3		rotation;
	t_vector3		angle;
	t_vector3		forward;
	t_vector3		right;
	t_vector3		up;

	t_vector3		force; // related to kinetic
	float			kinetic;

	t_texture		*texture;

	t_vector3_list	*vertices_in_world; // utils for gravity
	t_vector3_list	*next_vertices_in_world;

	t_vector3_list	*vertices;
	t_vector3_list	*uvs;
	t_vector3_list	*normales;
	t_face_list		*faces;

	char			*name;
	int				primitive;
	t_door			door;
}					t_mesh;

t_mesh			create_t_mesh(t_vector3 pos);
t_mesh			read_obj_file(char *path, t_vector3 pos, t_vector3 size, float gravity);
t_mesh			*initialize_t_mesh(t_vector3 pos);
void			delete_t_mesh(t_mesh mesh);
void			free_t_mesh(t_mesh *mesh);
void			t_mesh_add_point(t_mesh *dest, t_vector3 new_point);
void			t_mesh_add_uv(t_mesh *dest, t_vector3 new_uv);
void			t_mesh_add_face(t_mesh *dest, t_face new_face);
void 			t_mesh_set_texture(t_mesh *dest, t_texture *p_texture);
void 			t_mesh_set_color(t_mesh *dest, t_color p_color);
void			t_mesh_compute_normals(t_mesh *mesh);
void			t_mesh_compute_bubble_box(t_mesh *mesh);

void			t_mesh_move(t_mesh *dest, t_vector3 delta);

void			t_mesh_activate_gravity(t_mesh *dest, float gravity);
void			t_mesh_apply_force(t_mesh *dest);
void			t_mesh_set_force(t_mesh *dest, t_vector3 new_force);
void			t_mesh_add_force(t_mesh *dest, t_vector3 delta_force);

t_mesh			create_primitive_cube(t_vector3 coord, t_vector3 size, char *texture_path, float gravity);
t_mesh			create_primitive_plane(t_vector3 pos, t_vector3 size, char *texture_path, float gravity);
t_mesh			create_primitive_vertical_plane(t_vector3 pos, t_vector3 size, char *texture_path, float gravity);
t_mesh			create_primitive_skybox(t_vector3 pos, t_vector3 size, t_texture *p_texture);

void			t_mesh_rotate(t_mesh *mesh, t_vector3 delta_angle);
void			t_mesh_rotate_around_point(t_mesh *mesh, t_vector3 delta_angle, t_vector3 center);
void			t_mesh_look_at(t_mesh *mesh);

void			t_mesh_set_visibility(t_mesh *dest, int new_state);
void			t_mesh_compute_vertices_in_world(t_mesh *dest);
void			t_mesh_compute_next_vertices_in_world(t_mesh *dest, t_vector3 axis);

void			t_mesh_jump(t_mesh *body, t_vector3 jump);
void			t_mesh_resize(t_mesh *mesh, t_vector3 modif);
void			t_mesh_set_name(t_mesh *mesh, char *name);
void			t_mesh_move_door(t_mesh	*mesh);
#endif
