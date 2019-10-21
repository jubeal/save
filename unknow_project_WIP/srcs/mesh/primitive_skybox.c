#include "unknow_project.h"

static void	t_mesh_init_point_primitive_skybox(t_mesh *result, t_vector3 size)
{
	size.x -= EPSILON;
	size.y -= EPSILON;
	size.z -= EPSILON;
	t_mesh_add_point(result, create_t_vector3(-size.x / 2.0, -size.y / 2.0, -size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(size.x / 2.0, -size.y / 2.0, -size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(size.x / 2.0, -size.y / 2.0, size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(-size.x / 2.0, -size.y / 2.0, size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(-size.x / 2.0, size.y / 2.0, -size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(size.x / 2.0, size.y / 2.0, -size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(size.x / 2.0, size.y / 2.0, size.z / 2.0));
	t_mesh_add_point(result, create_t_vector3(-size.x / 2.0, size.y / 2.0, size.z / 2.0));
}

static void	t_mesh_init_uv_point_primitive_skybox(t_mesh *result)
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

static void	t_mesh_init_face_primitive_skybox_next(t_mesh *result, t_face tmp_face1, t_face tmp_face2)
{
	set_t_face_vertices(&tmp_face1, 2, 7, 6);
	set_t_face_uvs(&tmp_face1, 9, 8, 12);
	set_t_face_vertices(&tmp_face2, 7, 2, 3);
	set_t_face_uvs(&tmp_face2, 11, 12, 8);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 5, 2, 6);
	set_t_face_uvs(&tmp_face1, 9, 10, 5);
	set_t_face_vertices(&tmp_face2, 2, 5, 1);
	set_t_face_uvs(&tmp_face2, 6, 5, 10);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 3, 4, 7);
	set_t_face_uvs(&tmp_face1, 8, 4, 7);
	set_t_face_vertices(&tmp_face2, 4, 3, 0);
	set_t_face_uvs(&tmp_face2, 3, 7, 4);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
}

static void	t_mesh_init_face_primitive_skybox(t_mesh *result, t_face tmp_face1, t_face tmp_face2)
{
	set_t_face_vertices(&tmp_face1, 1, 3, 2);
	set_t_face_uvs(&tmp_face1, 4, 3, 1);
	set_t_face_vertices(&tmp_face2, 3, 1, 0);
	set_t_face_uvs(&tmp_face2, 0, 1, 3);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 7, 5, 6);
	set_t_face_uvs(&tmp_face1, 9, 5, 8);
	set_t_face_vertices(&tmp_face2, 5, 7, 4);
	set_t_face_uvs(&tmp_face2, 4, 8, 5);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 4, 1, 5);
	set_t_face_uvs(&tmp_face1, 5, 2, 4);
	set_t_face_vertices(&tmp_face2, 1, 4, 0);
	set_t_face_uvs(&tmp_face2, 1, 4, 2);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
}

t_mesh		create_primitive_skybox(t_vector3 pos, t_vector3 size, t_texture *p_texture)
{
	t_mesh	result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);
	result.primitive = -1;
	t_mesh_init_point_primitive_skybox(&result, size);
	t_mesh_init_uv_point_primitive_skybox(&result);
	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();
	t_mesh_init_face_primitive_skybox(&result, tmp_face1, tmp_face2);
	t_mesh_init_face_primitive_skybox_next(&result, tmp_face1, tmp_face2);
	t_mesh_compute_normals(&result);
	t_mesh_set_texture(&result, p_texture);
	return (result);
}
