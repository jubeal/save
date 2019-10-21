#include "unknow_project.h"

void		t_mesh_init_uv_point_primitive_plane(t_mesh *result)
{
	t_mesh_add_uv(result, create_t_vector3(0.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(0.0f, 1.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f, 1.0f, 0.0f));
}

t_mesh		create_primitive_plane(t_vector3 pos, t_vector3 size, char *texture_path, float gravity)
{
	t_mesh	result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);
	result.primitive = 0;
	result.size = create_t_vector3(size.x, size.y, size.z);
	t_mesh_activate_gravity(&result, gravity);
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, 0.0, -size.z / 2.0));
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, 0.0, -size.z / 2.0));
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, 0.0, size.z / 2.0));
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, 0.0, size.z / 2.0));
	t_mesh_init_uv_point_primitive_plane(&result);
	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();
	set_t_face_vertices(&tmp_face1, 2, 1, 3);
	set_t_face_uvs(&tmp_face1, 3, 2, 1);
	set_t_face_vertices(&tmp_face2, 0, 3, 1);
	set_t_face_uvs(&tmp_face2, 0, 1, 2);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);
	t_mesh_compute_normals(&result);
	t_mesh_compute_bubble_box(&result);
	if (texture_path != NULL)
		result.texture = png_load(texture_path);
	return (result);
}

void		t_mesh_init_uv_point_primitive_vertical_plane(t_mesh *result)
{
	t_mesh_add_uv(result, create_t_vector3(0.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f, 0.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(0.0f, 1.0f, 0.0f));
	t_mesh_add_uv(result, create_t_vector3(1.0f, 1.0f, 0.0f));
}
