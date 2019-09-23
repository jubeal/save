#include "unknow_project.h"

void		init_points_uv(t_mesh *mesh, t_face face, t_vector3 *points_uv)
{
	points_uv[0] = t_vector3_list_at(mesh->uvs, face.index_uvs[0]);
	points_uv[1] = t_vector3_list_at(mesh->uvs, face.index_uvs[1]);
	points_uv[2] = t_vector3_list_at(mesh->uvs, face.index_uvs[2]);
}

void		init_points(t_mesh *mesh, t_face face, t_vector3 *points)
{
	points[0] = add_vector3_to_vector3(t_vector3_list_at(mesh->vertices,\
									face.index_vertices[0]), mesh->pos);
	points[1] = add_vector3_to_vector3(t_vector3_list_at(mesh->vertices,\
									face.index_vertices[1]), mesh->pos);
	points[2] = add_vector3_to_vector3(t_vector3_list_at(mesh->vertices,\
									face.index_vertices[2]), mesh->pos);
}

t_triangle	init_triangle_clipped(t_mesh *mesh, t_camera *p_cam, int j)
{
	t_triangle	triangle;

	triangle.a = apply_t_camera(&(p_cam->clipping_list[j + 0]),\
											&(p_cam->projection));
	triangle.b = apply_t_camera(&(p_cam->clipping_list[j + 1]),\
											&(p_cam->projection));
	triangle.c = apply_t_camera(&(p_cam->clipping_list[j + 2]),\
											&(p_cam->projection));
	if (mesh->texture != NULL)
	{
		t_triangle_list_push_back(&(p_cam->triangle_texture_list), triangle);
		triangle.a = p_cam->clipping_list_uv[j + 0];
		triangle.b = p_cam->clipping_list_uv[j + 1];
		triangle.c = p_cam->clipping_list_uv[j + 2];
	}
	return (triangle);
}

void		apply_darkness_on_mesh_with_texture(t_mesh *mesh, t_camera *p_cam,\
								t_color darkness_color, t_triangle triangle)
{
	t_uv_list_push_back(&(p_cam->uv_list),\
						create_t_uv(triangle, mesh->texture));
	t_color_list_push_back(&(p_cam->darkness_list), darkness_color);
}

void		apply_darkness_on_mesh_without_texture(t_camera *p_cam, \
					t_face face, t_color darkness_color, t_triangle triangle)
{
	t_color_list_push_back(&(p_cam->color_list),\
					fuze_t_color(face.color, darkness_color));
	t_triangle_list_push_back(&(p_cam->triangle_color_list),\
													triangle);
}

void		find_darkness(t_mesh *mesh, t_face face, t_camera *cam,\
														int nb_clip)
{
	t_triangle	trgl;
	t_color		darkcol;
	float		darkness;
	int			j;

	darkness = (-dot_t_vector3(face.normale, cam->sun_direction) + 2)\
													/ (2 / (1 - 0.1));
	if (darkness > 1)
		darkness = 1;
	if (darkness < 0.1)
		darkness = 0.1;
	darkcol.r = darkness;
	darkcol.g = darkness;
	darkcol.b = darkness;
	darkcol.a = 0.4f;
	j = 0;
	while (j < nb_clip)
	{
		trgl = init_triangle_clipped(mesh, cam, j);
		if (mesh->texture == NULL)
			apply_darkness_on_mesh_without_texture(cam, face, darkcol, trgl);
		else
			apply_darkness_on_mesh_with_texture(mesh, cam, darkcol, trgl);
		j += 3;
	}
}

void		how_many_points_clipped(t_mesh *mesh, t_face face, t_camera *p_cam)
{
	t_vector3	points[3];
	t_vector3	points_uv[3];
	int			nb_clipped;
	float		result;

	init_points(mesh, face, &*points);
	if (mesh->texture != NULL)
		init_points_uv(mesh, face, &*points_uv);
	result = dot_t_vector3(face.normale, normalize_t_vector3(\
					substract_vector3_to_vector3(points[0], p_cam->pos)));
	if (result < 0)
	{
		points[0] = mult_vector3_by_matrix(points[0], (p_cam->view));
		points[1] = mult_vector3_by_matrix(points[1], (p_cam->view));
		points[2] = mult_vector3_by_matrix(points[2], (p_cam->view));
		if (mesh->texture != NULL)
			nb_clipped = clip_triangle_to_plane(p_cam, points, points_uv);
		else
			nb_clipped = clip_triangle_to_plane(p_cam, points, NULL);
		find_darkness(mesh, face, p_cam, nb_clipped);
	}
}

void		draw_t_mesh(t_camera *p_cam, t_mesh *mesh)
{
	int		i;
	t_face	face;

	i = -1;
	if (mesh->is_visible == BOOL_FALSE)
		return ;
	while (++i < mesh->faces->size)
	{
		face = t_face_list_at(mesh->faces, i);
		how_many_points_clipped(mesh, face, p_cam);
	}
}
