/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboutin <gboutin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:31:13 by adjouber          #+#    #+#             */
/*   Updated: 2019/11/22 10:18:55 by gboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

t_mesh			init_primitive(char **line_split, char *texture_path)
{
	t_mesh		mesh;
	t_vector4	vec[2];

	vec[0] = create_t_vector4(ft_atof(line_split[2]),
								ft_atof(line_split[3]),
								ft_atof(line_split[4]));
	vec[1] = create_t_vector4(ft_atof(line_split[5]),
								ft_atof(line_split[6]),
								ft_atof(line_split[7]));
	if (ft_strcmp(line_split[0], "plane:") == 0)
		mesh = create_primitive_plane(vec[0], vec[1],
			texture_path, ft_atof(line_split[9]));
	else if (ft_strcmp(line_split[0], "cube:") == 0)
		mesh = create_primitive_cube(vec[0], vec[1],
			texture_path, ft_atof(line_split[9]));
	else if (ft_strcmp(line_split[0], "item:") == 0)
	{
		mesh = create_primitive_cube(vec[0], vec[1],
			texture_path, ft_atof(line_split[9]));
		mesh.collectible = 1;
	}
	else if (line_split[0][0] == '#')
		mesh = read_obj_file(&line_split[0][1], vec[0], vec[1],
			ft_atof(line_split[10]));
	return (mesh);
}

t_mesh			init_texture(char **line_split)
{
	t_mesh		mesh;
	char		*texture_path;
	t_color		color;

	texture_path = NULL;
	if (ft_strcmp(line_split[8], "NULL") != 0)
		texture_path = line_split[8];
	else
		color = create_t_color(ft_atof(line_split[13]),
			ft_atof(line_split[14]),
			ft_atof(line_split[15]),
			ft_atof(line_split[16]));
	mesh = init_primitive(line_split, texture_path);
	if (texture_path == NULL)
		t_mesh_set_color(&mesh, color);
	return (mesh);
}

void			set_mesh(t_mesh *mesh, char **line_split)
{
	t_mesh_rotate(mesh, create_t_vector4(ft_atof(line_split[10]),
		ft_atof(line_split[11]), ft_atof(line_split[12])));
	mesh->hp = ft_atoi(line_split[17]);
	if (ft_strcmp(line_split[ft_tablen(line_split) - 1], "*") == 0)
		t_mesh_set_visibility(mesh, BOOL_FALSE);
	if (ft_strcmp(line_split[ft_tablen(line_split) - 1], "#") == 0)
		mesh->no_hitbox = 1;
	else
		mesh->no_hitbox = 0;
	t_mesh_set_name(mesh, line_split[1]);
}

t_mesh_list		*read_map_file(int fd)
{
	t_mesh		mesh;
	t_mesh_list	*result;
	char		*line;
	char		**split;

	result = initialize_t_mesh_list();
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) != 0)
		{
			split = ft_strsplit(line, ' ');
			if (ft_strcmp(split[0], "plane:") == 0
				|| ft_strcmp(split[0], "cube:") == 0
				|| ft_strcmp(split[0], "item:") == 0 || split[0][0] == '#')
			{
				mesh = init_texture(split);
				set_mesh(&mesh, split);
				t_mesh_list_push_back(result, mesh);
			}
			ft_freetab(split);
		}
		free(line);
	}
	free(line);
	return (result);
}
