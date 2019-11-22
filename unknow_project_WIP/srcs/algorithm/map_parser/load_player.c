/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboutin <gboutin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:30:45 by adjouber          #+#    #+#             */
/*   Updated: 2019/11/22 10:18:51 by gboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

t_mesh			init_mesh(char **line_split)
{
	t_mesh		mesh;
	t_vector4	vector[3];

	vector[0] = create_t_vector4(ft_atof(line_split[2]),
								ft_atof(line_split[3]) + 0.2,
								ft_atof(line_split[4]));
	vector[1] = create_t_vector4(ft_atof(line_split[5]),
								ft_atof(line_split[6]),
								ft_atof(line_split[7]));
	vector[2] = create_t_vector4(ft_atof(line_split[10]),
								ft_atof(line_split[11]),
								ft_atof(line_split[12]));
	mesh = create_primitive_cube(vector[0], vector[1], NULL,
		ft_atof(line_split[9]));
	t_mesh_rotate(&mesh, vector[2]);
	mesh.hp = ft_atoi(line_split[17]);
	mesh.no_hitbox = 0;
	mesh.primitive = -1;
	t_mesh_set_name(&mesh, line_split[1]);
	return (mesh);
}

void			init_player(t_player *player, char **line_split)
{
	player->hp = ft_atoi(line_split[17]);
	player->armor = ft_atoi(line_split[18]);
	player->fuel = ft_atoi(line_split[19]);
	player->weapons[0] = create_t_weapons(0,
			ft_atoi(line_split[20]), ft_atoi(line_split[21]));
	player->weapons[1] = create_t_weapons(1,
			ft_atoi(line_split[22]), ft_atoi(line_split[23]));
	player->weapons[2] = create_t_weapons(2,
			ft_atoi(line_split[24]), ft_atoi(line_split[25]));
	player->weapons[3] = create_t_weapons(3,
			ft_atoi(line_split[26]), ft_atoi(line_split[27]));
	player->weapons[4] = create_t_weapons(4,
			ft_atoi(line_split[28]), ft_atoi(line_split[29]));
	player->red_card = ft_atoi(line_split[30]);
	player->blue_card = ft_atoi(line_split[31]);
	player->green_card = ft_atoi(line_split[32]);
	player->current_weapon = &player->weapons[0];
}

t_player		*read_player(int fd, t_camera *main_camera)
{
	t_player	*player;
	char		*line;
	char		**line_split;
	t_vector4	vector[3];

	player = initialize_t_player(main_camera);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) != 0)
		{
			line_split = ft_strsplit(line, ' ');
			if (ft_strcmp(line_split[0], "player:") == 0)
			{
				player->hitbox = init_mesh(line_split);
				t_mesh_set_color(&player->hitbox,
						create_t_color(0.5, 0.6, 0.0, 1.0));
				init_player(player, line_split);
			}
			ft_freetab(line_split);
		}
		free(line);
	}
	free(line);
	return (player);
}
