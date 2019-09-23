#include "unknow_project.h"

static void	t_mesh_init_point_primitive_cube(t_mesh *result, t_vector3 size)
{
	size.x -= EPSILON;
	size.y -= EPSILON;
	size.z -= EPSILON;
	t_mesh_add_point(result, create_t_vector3(0, 0, 0));
	t_mesh_add_point(result, create_t_vector3(size.x, 0, 0));
	t_mesh_add_point(result, create_t_vector3(size.x, 0, size.z));
	t_mesh_add_point(result, create_t_vector3(0, 0, size.z));
	t_mesh_add_point(result, create_t_vector3(0, size.y, 0));
	t_mesh_add_point(result, create_t_vector3(size.x, size.y, 0));
	t_mesh_add_point(result, create_t_vector3(size.x, size.y, size.z));
	t_mesh_add_point(result, create_t_vector3(0, size.y, size.z));
}

static void	t_mesh_init_uv_point_primitive_cube(t_mesh *result)
{
	t_mesh_add_uv(result, create_t_vector3(0.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f / 3.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(2.0f / 3.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(0.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f / 3.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(2.0f / 3.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(0.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f / 3.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(2.0f / 3.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f / 3.0f, 1.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(2.0f / 3.0f, 1.0f, 0.0f));
}

static void	t_mesh_init_face_primitive_cube_next(t_mesh *result, t_face tmp_face1, t_face tmp_face2)
{
	set_t_face_vertices(&tmp_face1, 6, 7, 2);
	set_t_face_uvs(&tmp_face1, 9, 8, 12);
	set_t_face_vertices(&tmp_face2, 3, 2, 7);
	set_t_face_uvs(&tmp_face2, 11, 12, 8);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 6, 2, 5);
	set_t_face_uvs(&tmp_face1, 9, 10, 5);
	set_t_face_vertices(&tmp_face2, 1, 5, 2);
	set_t_face_uvs(&tmp_face2, 6, 5, 10);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 7, 4, 3);
	set_t_face_uvs(&tmp_face1, 8, 4, 7);
	set_t_face_vertices(&tmp_face2, 0, 3, 4);
	set_t_face_uvs(&tmp_face2, 3, 7, 4);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
}

static void	t_mesh_init_face_primitive_cube(t_mesh *result, t_face tmp_face1, t_face tmp_face2)
{
	set_t_face_vertices(&tmp_face1, 2, 3, 1);
	set_t_face_uvs(&tmp_face1, 4, 3, 1);
	set_t_face_vertices(&tmp_face2, 0, 1, 3);
	set_t_face_uvs(&tmp_face2, 0, 1, 3);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 6, 5, 7);
	set_t_face_uvs(&tmp_face1, 9, 5, 8);
	set_t_face_vertices(&tmp_face2, 4, 7, 5);
	set_t_face_uvs(&tmp_face2, 4, 8, 5);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 5, 1, 4);
	set_t_face_uvs(&tmp_face1, 5, 2, 4);
	set_t_face_vertices(&tmp_face2, 0, 4, 1);
	set_t_face_uvs(&tmp_face2, 1, 4, 2);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
}

t_mesh		create_primitive_cube(t_vector3 pos, t_vector3 size, t_texture *p_texture, float gravity, char *name)
{
	t_mesh	result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos, name);
	t_mesh_activate_gravity(&result, gravity);
	t_mesh_init_point_primitive_cube(&result, size);
	t_mesh_init_uv_point_primitive_cube(&result);
	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();
	t_mesh_init_face_primitive_cube(&result, tmp_face1, tmp_face2);
	t_mesh_init_face_primitive_cube_next(&result, tmp_face1, tmp_face2);
	t_mesh_compute_normals(&result);
	t_mesh_compute_bubble_box(&result);
	t_mesh_set_texture(&result, p_texture);
	return (result);
}
