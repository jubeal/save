#include "unknow_project.h"

int			clip_triangle_to_plane(t_camera *p_camera, t_vector4 *p_points, t_vector4 *p_points_uv)
{
	t_vector4 		outside_points[3];
	t_vector4 		inside_points[3];
	t_vector4 		outside_points_uv[3];
	t_vector4 		inside_points_uv[3];
	t_vector4		forward;
	t_vector4		plane_center;
	t_vector4		*clipping_list;
	t_vector4		*clipping_list_uv;
	int				outside_nb;
	int				inside_nb;
	float			dist[3];

	clipping_list = p_camera->clipping_list;
	clipping_list_uv = p_camera->clipping_list_uv;
	forward = create_t_vector4(0, 0, 1);
	plane_center = create_t_vector4(0, 0, p_camera->near);

	dist[0] = calc_distance_to_plane(forward, plane_center, p_points[0]); //calcul de la distance du triangle par rapport au plan
	dist[1] = calc_distance_to_plane(forward, plane_center, p_points[1]);
	dist[2] = calc_distance_to_plane(forward, plane_center, p_points[2]);

	outside_nb = 0;
	inside_nb = 0;
	for (int i = 0; i < 3; i++)
	{
		if (dist[i] >= 0)
		{
			inside_points[inside_nb] = p_points[i];
			if (p_points_uv != NULL)
				inside_points_uv[inside_nb] = p_points_uv[i];
			inside_nb++;
		}
		else
		{
			outside_points[outside_nb] = p_points[i];
			if (p_points_uv != NULL)
				outside_points_uv[outside_nb] = p_points_uv[i];
			outside_nb++;
		}
	}

	if (inside_nb == 1) // si 1 point a l'interieur, creation de 2 nouveaux point pour refaire le triangle
	{
		clipping_list[0] = inside_points[0];
		clipping_list[1] = intersect_plane_by_line(forward, plane_center, outside_points[0], inside_points[0]);
		clipping_list[2] = intersect_plane_by_line(forward, plane_center, outside_points[1], inside_points[0]);

		if (p_points_uv != NULL)
		{
			clipping_list_uv[0] = inside_points_uv[0];

			clipping_list_uv[1] = interpolate_vector4_over_line(
												interpolate_ratio(inside_points[0].x, outside_points[0].x, clipping_list[1].x),
												interpolate_ratio(inside_points[0].y, outside_points[0].y, clipping_list[1].y),
												inside_points_uv[0], outside_points_uv[0]);
			clipping_list_uv[2] = interpolate_vector4_over_line(
												interpolate_ratio(inside_points[0].x, outside_points[1].x, clipping_list[2].x),
												interpolate_ratio(inside_points[0].y, outside_points[1].y, clipping_list[2].y),
												inside_points_uv[0], outside_points_uv[1]);
		}

		return (3);
	}
	else if (inside_nb == 2) // si 2 points a l'interieur, creation de 2 nouveaux point pour creer 2 triangles
	{
		clipping_list[0] = inside_points[0];
		clipping_list[1] = inside_points[1];
		clipping_list[2] = intersect_plane_by_line(forward, plane_center, inside_points[0], outside_points[0]);

		if (p_points_uv != NULL)
		{
			clipping_list_uv[0] = inside_points_uv[0];
			clipping_list_uv[1] = inside_points_uv[1];
			clipping_list_uv[2] = interpolate_vector4_over_line(
											interpolate_ratio(inside_points[0].x, outside_points[0].x, clipping_list[2].x),
											interpolate_ratio(inside_points[0].y, outside_points[0].y, clipping_list[2].y),
											inside_points_uv[0], outside_points_uv[0]);
		}


		clipping_list[3] = inside_points[1];
		clipping_list[4] = intersect_plane_by_line(forward, plane_center, inside_points[0], outside_points[0]);
		clipping_list[5] = intersect_plane_by_line(forward, plane_center, inside_points[1], outside_points[0]);

		if (p_points_uv != NULL)
		{
			clipping_list_uv[3] = inside_points_uv[1];
			clipping_list_uv[4] = interpolate_vector4_over_line(
											interpolate_ratio(inside_points[0].x, outside_points[0].x, clipping_list[4].x),
											interpolate_ratio(inside_points[0].y, outside_points[0].y, clipping_list[4].y),
											inside_points_uv[0], outside_points_uv[0]);
			clipping_list_uv[5] = interpolate_vector4_over_line(
											interpolate_ratio(inside_points[1].x, outside_points[0].x, clipping_list[5].x),
											interpolate_ratio(inside_points[1].y, outside_points[0].y, clipping_list[5].y),
											inside_points_uv[1], outside_points_uv[0]);
		}

		return (6);
	}
	if (inside_nb == 3) // si 3 point a l'interieur, rien a faire
	{
		clipping_list[0] = inside_points[0];
		clipping_list[1] = inside_points[1];
		clipping_list[2] = inside_points[2];

		if (p_points_uv != NULL)
		{
			clipping_list_uv[0] = inside_points_uv[0];
			clipping_list_uv[1] = inside_points_uv[1];
			clipping_list_uv[2] = inside_points_uv[2];
		}

		return (3);
	}

	return (0);
}
