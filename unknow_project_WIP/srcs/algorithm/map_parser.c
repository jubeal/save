#include "unknow_project.h"

t_mesh_list		*read_map_file(char *path)
{
	t_mesh		mesh;
	t_mesh_list	*result;
	char		*line;
	char		**line_split;
	int			fd;
	char		*texture_path;
	t_vector3	vector[3];
	char		*obj_path[256];
	int			i;
	t_color 	color;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	 	error_exit(-7000, "impossible fd");
	result = initialize_t_mesh_list();
	while (get_next_line(fd, &line) > 0)
	{
		texture_path = NULL;
		if (ft_strlen(line) != 0)
		{
			line_split = ft_strsplit(line, ' ');
			i = 0;
			if (ft_strcmp(line_split[0], "#") == 0)
				i++;
			if (ft_strcmp(line_split[0], "plane:") == 0 || ft_strcmp(line_split[0], "cube:") == 0 || i > 0)
			{
				vector[0] = create_t_vector3(ft_atof(line_split[2 + i]),
											ft_atof(line_split[3 + i]),
											ft_atof(line_split[4 + i]));
				vector[1] = create_t_vector3(ft_atof(line_split[5 + i]),
											ft_atof(line_split[6 + i]),
											ft_atof(line_split[7 + i]));
				vector[2] = create_t_vector3(ft_atof(line_split[10 + i]),
											ft_atof(line_split[11 + i]),
											ft_atof(line_split[12 + i]));

				if (ft_strcmp(line_split[8 + i], "NULL") != 0)
					texture_path = line_split[8 + i];
				else if (ft_tablen(line_split) == 18 + i)
					color = create_t_color(ft_atof(line_split[13 + i]), ft_atof(line_split[14 + i]), ft_atof(line_split[15 + i]), ft_atof(line_split[16 + i]));
				if (ft_strcmp(line_split[0], "plane:") == 0)
					mesh = create_primitive_plane(vector[0], vector[1], texture_path, ft_atof(line_split[9 + i]));
				else if (ft_strcmp(line_split[0], "cube:") == 0)
					mesh = create_primitive_cube(vector[0], vector[1], texture_path, ft_atof(line_split[9 + i]));
				else if (i > 0)
					mesh = read_obj_file(line_split[1], vector[0], vector[1], ft_atof(line_split[10 + i]));
				if (texture_path == NULL)
					t_mesh_set_color(&mesh, color);
				t_mesh_rotate(&mesh, vector[2]);
				if (ft_strcmp(line_split[ft_tablen(line_split) - 1], "*") == 0)
					t_mesh_set_visibility(&mesh, BOOL_FALSE);
				mesh.collectible = ft_atoi(line_split[17 + i]);
				t_mesh_set_name(&mesh, line_split[1 + i]);
				t_mesh_list_push_back(result, mesh);
			}
		}
		free(line);
	}
	free(line);
	ft_freetab(line_split);
	close(fd);
	return(result);
}
