#include "unknow_project.h"

void	draw_skybox(t_window *p_win, t_camera *p_cam, t_mesh *mesh)
{
	int			nb_clipped;
	t_uv 		tmp_uv;
	t_triangle	triangle;
	t_vector4	points[3];
	t_vector4	points_uv[3];
	float 		result;

	if (mesh->is_visible == BOOL_FALSE)
		return ;

	for (int i = 0; i < mesh->faces->size; i++)
	{
		t_face face = t_face_list_at(mesh->faces, i); // recuperation la face du volume a draw

		points[0] = add_vector4_to_vector4(t_vector4_list_at(mesh->vertices, face.index_vertices[0]), mesh->pos);
		points[1] = add_vector4_to_vector4(t_vector4_list_at(mesh->vertices, face.index_vertices[1]), mesh->pos);
		points[2] = add_vector4_to_vector4(t_vector4_list_at(mesh->vertices, face.index_vertices[2]), mesh->pos);

		if (mesh->texture != NULL)
		{
			points_uv[0] = t_vector4_list_at(mesh->uvs, face.index_uvs[0]);
			points_uv[1] = t_vector4_list_at(mesh->uvs, face.index_uvs[1]);
			points_uv[2] = t_vector4_list_at(mesh->uvs, face.index_uvs[2]);
		}


		result = dot_t_vector4(face.normale, normalize_t_vector4(substract_vector4_to_vector4(points[0], p_cam->pos)));

		if (result < 0)
		{
			points[0] = mult_vector4_by_matrix(points[0], (p_cam->view));
			points[1] = mult_vector4_by_matrix(points[1], (p_cam->view));
			points[2] = mult_vector4_by_matrix(points[2], (p_cam->view));

			if (mesh->texture != NULL)
			 	nb_clipped = clip_triangle_to_plane(p_cam, points, points_uv);
			else
			 	nb_clipped = clip_triangle_to_plane(p_cam, points, NULL);

			for (int j = 0; j < nb_clipped; j += 3)
			{
				triangle.a = apply_t_camera(&(p_cam->clipping_list[j + 0]), &(p_cam->projection)); // applique la position de la camera
				triangle.b = apply_t_camera(&(p_cam->clipping_list[j + 1]), &(p_cam->projection));
				triangle.c = apply_t_camera(&(p_cam->clipping_list[j + 2]), &(p_cam->projection));

				if (mesh->texture == NULL)
				{
					t_color_list_push_back(&(p_cam->color_list), face.color);
					t_triangle_list_push_back(&(p_cam->triangle_color_list), triangle);
				}
				else
				{
					t_triangle_list_push_back(&(p_cam->triangle_texture_list), triangle);
					triangle.a = p_cam->clipping_list_uv[j + 0];
					triangle.b = p_cam->clipping_list_uv[j + 1];
					triangle.c = p_cam->clipping_list_uv[j + 2];
					tmp_uv = create_t_uv(triangle, mesh->texture);
					t_uv_list_push_back(&(p_cam->uv_list), tmp_uv);
				}
			}
		}
	}
}