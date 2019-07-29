#include "unknow_project.h"

t_mesh		create_primitive_cube(t_vector3 pos, t_vector3 size, t_texture *p_texture, float gravity)
{
	t_mesh 	result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);

	t_mesh_activate_gravity(&result, gravity);

	size.x -= EPSILON;
	size.y -= EPSILON;
	size.z -= EPSILON;

	//Bottom part
	t_mesh_add_point(&result, create_t_vector3(0, 0, 0)); //A
	t_mesh_add_point(&result, create_t_vector3(size.x, 0, 0)); //B
	t_mesh_add_point(&result, create_t_vector3(size.x, 0, size.z)); //C
	t_mesh_add_point(&result, create_t_vector3(0, 0, size.z)); //D

	//Top part
	t_mesh_add_point(&result, create_t_vector3(0, size.y, 0)); //E
	t_mesh_add_point(&result, create_t_vector3(size.x, size.y, 0)); //F
	t_mesh_add_point(&result, create_t_vector3(size.x, size.y, size.z)); //G
	t_mesh_add_point(&result, create_t_vector3(0, size.y, size.z)); //H

	t_mesh_add_uv(&result, create_t_vector3(0.0f, 0.0f, 0.0f)); // 0
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 0.0f, 0.0f)); // 1
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 0.0f, 0.0f)); // 2
	t_mesh_add_uv(&result, create_t_vector3(0.0f, 1.0f / 3.0f, 0.0f)); // 3
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 1.0f / 3.0f, 0.0f)); // 4
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 1.0f / 3.0f, 0.0f)); // 5
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 1.0f / 3.0f, 0.0f)); // 6
	t_mesh_add_uv(&result, create_t_vector3(0.0f, 2.0f / 3.0f, 0.0f)); // 7
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 2.0f / 3.0f, 0.0f)); // 8
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 2.0f / 3.0f, 0.0f)); // 9
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 2.0f / 3.0f, 0.0f)); // 10
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 1.0f, 0.0f)); // 11
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 1.0f, 0.0f)); // 12

	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();

	set_t_face_vertices(&tmp_face1, 2, 3, 1); // FACE DOWN
	set_t_face_uvs(&tmp_face1, 4, 3, 1);
	set_t_face_vertices(&tmp_face2, 0, 1, 3);
	set_t_face_uvs(&tmp_face2, 0, 1, 3);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 6, 5, 7); // FACE TOP
	set_t_face_uvs(&tmp_face1, 9, 5, 8);
	set_t_face_vertices(&tmp_face2, 4, 7, 5);
	set_t_face_uvs(&tmp_face2, 4, 8, 5);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 5, 1, 4); // FACE FRONT
	set_t_face_uvs(&tmp_face1, 5, 2, 4);
	set_t_face_vertices(&tmp_face2, 0, 4, 1);
	set_t_face_uvs(&tmp_face2, 1, 4, 2);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 6, 7, 2); // FACE BACK
	set_t_face_uvs(&tmp_face1, 9, 8, 12);
	set_t_face_vertices(&tmp_face2, 3, 2, 7);
	set_t_face_uvs(&tmp_face2, 11, 12, 8);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 6, 2, 5); // FACE RIGHT
	set_t_face_uvs(&tmp_face1, 9, 10, 5);
	set_t_face_vertices(&tmp_face2, 1, 5, 2);
	set_t_face_uvs(&tmp_face2, 6, 5, 10);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 7, 4, 3); // FACE LEFT
	set_t_face_uvs(&tmp_face1, 8, 4, 7);
	set_t_face_vertices(&tmp_face2, 0, 3, 4);
	set_t_face_uvs(&tmp_face2, 3, 7, 4);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	t_mesh_compute_normals(&result);

	t_mesh_compute_bubble_box(&result);

	t_mesh_set_texture(&result, p_texture);

	return (result);
}

t_mesh		create_primitive_plane(t_vector3 pos, t_vector3 size, t_texture *p_texture, float gravity)
{
	t_mesh result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);

	t_mesh_activate_gravity(&result, gravity);

	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, 0.0, -size.z / 2.0));
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, 0.0, -size.z / 2.0));
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, 0.0, size.z / 2.0));
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, 0.0, size.z / 2.0));

	t_mesh_add_uv(&result, create_t_vector3(0.0f, 0.0f, 0.0f));
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 0.0f, 0.0f));
	t_mesh_add_uv(&result, create_t_vector3(0.0f, 1.0f, 0.0f));
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 1.0f, 0.0f));

	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();

	set_t_face_vertices(&tmp_face1, 2, 1, 3); // FACE UP
	set_t_face_uvs(&tmp_face1, 3, 2, 1);
	set_t_face_vertices(&tmp_face2, 0, 3, 1);
	set_t_face_uvs(&tmp_face2, 0, 1, 2);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	t_mesh_compute_normals(&result);

	t_mesh_compute_bubble_box(&result);

	t_mesh_set_texture(&result, p_texture);

	return (result);
}

t_mesh		create_primitive_vertical_plane(t_vector3 pos, t_vector3 size, t_texture *p_texture, float gravity)
{
	t_mesh result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);

	t_mesh_activate_gravity(&result, gravity);

	t_mesh_add_point(&result, create_t_vector3(-size.x, -size.z, 0.0));
	t_mesh_add_point(&result, create_t_vector3(size.x, -size.z, 0.0));
	t_mesh_add_point(&result, create_t_vector3(size.x, size.z, 0.0));
	t_mesh_add_point(&result, create_t_vector3(-size.x, size.z, 0.0));

	t_mesh_add_uv(&result, create_t_vector3(0.0f, 0.0f, 0.0f));
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 0.0f, 0.0f));
	t_mesh_add_uv(&result, create_t_vector3(0.0f, 1.0f, 0.0f));
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 1.0f, 0.0f));

	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();

	set_t_face_vertices(&tmp_face1, 2, 1, 3); // FACE DOWN
	set_t_face_uvs(&tmp_face1, 4, 3, 1);
	set_t_face_vertices(&tmp_face2, 0, 1, 3);
	set_t_face_uvs(&tmp_face2, 0, 1, 3);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	t_mesh_compute_normals(&result);

	t_mesh_compute_bubble_box(&result);

	t_mesh_set_texture(&result, p_texture);

	return (result);
}

t_mesh	create_primitive_skybox(t_vector3 pos, t_vector3 size, t_texture *p_texture)
{
	t_mesh 	result;
	t_face	tmp_face1;
	t_face	tmp_face2;

	result = create_t_mesh(pos);

	// t_mesh_activate_gravity(&result, 0.0);

	size.x -= EPSILON;
	size.y -= EPSILON;
	size.z -= EPSILON;

	//Bottom part
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, -size.y / 2.0, -size.z / 2.0)); //A
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, -size.y / 2.0, -size.z / 2.0)); //B
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, -size.y / 2.0, size.z / 2.0)); //C
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, -size.y / 2.0, size.z / 2.0)); //D

	//Top part
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, size.y / 2.0, -size.z / 2.0)); //E
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, size.y / 2.0, -size.z / 2.0)); //F
	t_mesh_add_point(&result, create_t_vector3(size.x / 2.0, size.y / 2.0, size.z / 2.0)); //G
	t_mesh_add_point(&result, create_t_vector3(-size.x / 2.0, size.y / 2.0, size.z / 2.0)); //H

	t_mesh_add_uv(&result, create_t_vector3(0.0f, 0.0f, 0.0f)); // 0
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 0.0f, 0.0f)); // 1
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 0.0f, 0.0f)); // 2
	t_mesh_add_uv(&result, create_t_vector3(0.0f, 1.0f / 3.0f, 0.0f)); // 3
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 1.0f / 3.0f, 0.0f)); // 4
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 1.0f / 3.0f, 0.0f)); // 5
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 1.0f / 3.0f, 0.0f)); // 6
	t_mesh_add_uv(&result, create_t_vector3(0.0f, 2.0f / 3.0f, 0.0f)); // 7
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 2.0f / 3.0f, 0.0f)); // 8
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 2.0f / 3.0f, 0.0f)); // 9
	t_mesh_add_uv(&result, create_t_vector3(1.0f, 2.0f / 3.0f, 0.0f)); // 10
	t_mesh_add_uv(&result, create_t_vector3(1.0f / 3.0f, 1.0f, 0.0f)); // 11
	t_mesh_add_uv(&result, create_t_vector3(2.0f / 3.0f, 1.0f, 0.0f)); // 12

	tmp_face1 = create_t_face();
	tmp_face2 = create_t_face();

	set_t_face_vertices(&tmp_face1, 1, 3, 2); // FACE DOWN
	set_t_face_uvs(&tmp_face1, 4, 3, 1);
	set_t_face_vertices(&tmp_face2, 3, 1, 0);
	set_t_face_uvs(&tmp_face2, 0, 1, 3);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 7, 5, 6); // FACE TOP
	set_t_face_uvs(&tmp_face1, 9, 5, 8);
	set_t_face_vertices(&tmp_face2, 5, 7, 4);
	set_t_face_uvs(&tmp_face2, 4, 8, 5);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 4, 1, 5); // FACE FRONT
	set_t_face_uvs(&tmp_face1, 5, 2, 4);
	set_t_face_vertices(&tmp_face2, 1, 4, 0);
	set_t_face_uvs(&tmp_face2, 1, 4, 2);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 2, 7, 6); // FACE BACK
	set_t_face_uvs(&tmp_face1, 9, 8, 12);
	set_t_face_vertices(&tmp_face2, 7, 2, 3);
	set_t_face_uvs(&tmp_face2, 11, 12, 8);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 5, 2, 6); // FACE RIGHT
	set_t_face_uvs(&tmp_face1, 9, 10, 5);
	set_t_face_vertices(&tmp_face2, 2, 5, 1);
	set_t_face_uvs(&tmp_face2, 6, 5, 10);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	set_t_face_vertices(&tmp_face1, 3, 4, 7); // FACE LEFT
	set_t_face_uvs(&tmp_face1, 8, 4, 7);
	set_t_face_vertices(&tmp_face2, 4, 3, 0);
	set_t_face_uvs(&tmp_face2, 3, 7, 4);
	t_mesh_add_face(&result, tmp_face1);
	t_mesh_add_face(&result, tmp_face2);

	t_mesh_compute_normals(&result);

	t_mesh_set_texture(&result, p_texture);

	return (result);
}
