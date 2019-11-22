#include "unknow_project.h"

static void	t_mesh_init_point_primitive_cube(t_mesh *result, t_vector4 size)
{
	size.x -= EPSILON;
	size.y -= EPSILON;
	size.z -= EPSILON;
	t_mesh_add_point(result, create_t_vector4(0, 0, 0));
	t_mesh_add_point(result, create_t_vector4(size.x, 0, 0));
	t_mesh_add_point(result, create_t_vector4(size.x, 0, size.z));
	t_mesh_add_point(result, create_t_vector4(0, 0, size.z));
	t_mesh_add_point(result, create_t_vector4(0, size.y, 0));
	t_mesh_add_point(result, create_t_vector4(size.x, size.y, 0));
	t_mesh_add_point(result, create_t_vector4(size.x, size.y, size.z));
	t_mesh_add_point(result, create_t_vector4(0, size.y, size.z));
}

static void	t_mesh_init_uv_point_primitive_cube(t_mesh *result)
{
	t_mesh_add_uv(result, create_t_vector4(0.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(1.0f / 3.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(2.0f / 3.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(0.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(1.0f / 3.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(2.0f / 3.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(1.0f, 1.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(0.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(1.0f / 3.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(2.0f / 3.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(1.0f, 2.0f / 3.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(1.0f / 3.0f, 1.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector4(2.0f / 3.0f, 1.0f, 0.0f));
}

static void	t_mesh_init_face_primitive_cube_next(t_mesh *result, t_face tmp_face1, t_face tmp_face2)
{
	set_t_face_vertices(&tmp_face1, 7, 3, 6);
	set_t_face_uvs(&tmp_face1, 8, 11, 9);
	set_t_face_vertices(&tmp_face2, 2, 6, 3);
	set_t_face_uvs(&tmp_face2, 12, 9, 11);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 6, 2, 5);
	set_t_face_uvs(&tmp_face1, 5, 6, 9);
	set_t_face_vertices(&tmp_face2, 1, 5, 2);
	set_t_face_uvs(&tmp_face2, 10, 9, 6);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 7, 4, 3);
	set_t_face_uvs(&tmp_face1, 4, 8, 3);
	set_t_face_vertices(&tmp_face2, 0, 3, 4);
	set_t_face_uvs(&tmp_face2, 7, 3, 8);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
}

static void	t_mesh_init_face_primitive_cube(t_mesh *result, t_face tmp_face1, t_face tmp_face2)
{
	set_t_face_vertices(&tmp_face1, 2, 3, 1);
	set_t_face_uvs(&tmp_face1, 0, 1, 3);
	set_t_face_vertices(&tmp_face2, 0, 1, 3);
	set_t_face_uvs(&tmp_face2, 4, 3, 1);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 6, 5, 7);
	set_t_face_uvs(&tmp_face1, 8, 4, 9);
	set_t_face_vertices(&tmp_face2, 4, 7, 5);
	set_t_face_uvs(&tmp_face2, 5, 9, 4);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
	set_t_face_vertices(&tmp_face1, 5, 1, 4);
	set_t_face_uvs(&tmp_face1, 4, 1, 5);
	set_t_face_vertices(&tmp_face2, 0, 4, 1);
	set_t_face_uvs(&tmp_face2, 2, 5, 1);
	t_mesh_add_face(result, tmp_face1);
	t_mesh_add_face(result, tmp_face2);
}

t_mesh		create_primitive_cube(t_vector4 pos, t_vector4 size, char *texture_path, float gravity)
{
	t_mesh	result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);
	result.primitive = 1;
	result.size = create_t_vector4(size.x, size.y, size.z);
	t_mesh_activate_gravity(&result, gravity);
	t_mesh_init_point_primitive_cube(&result, size);
	t_mesh_init_uv_point_primitive_cube(&result);
	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();
	t_mesh_init_face_primitive_cube(&result, tmp_face1, tmp_face2);
	t_mesh_init_face_primitive_cube_next(&result, tmp_face1, tmp_face2);
	t_mesh_compute_normals(&result);
	t_mesh_compute_bubble_box(&result);
	if (texture_path != NULL)
		result.texture = png_load(texture_path);
	return (result);
}
