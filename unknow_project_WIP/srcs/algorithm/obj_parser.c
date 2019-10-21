#include "unknow_project.h"

t_mesh		read_obj_file(char *path, t_vector3 pos, t_vector3 size, float gravity)
{
	t_mesh	result;
	char	*line;
	char	**line_split;
	char	**tab;
	int		index[4];
	int		index_uv[4];
	int		fd;
	int		i;
	t_face	tmp_face;

	result = create_t_mesh(pos);
	t_mesh_activate_gravity(&result, gravity);
	tmp_face = create_t_face();

	fd = open(path, O_RDONLY);

	for (i = 0; i < 4; i++)
	{
		index[i] = 0;
		index_uv[i] = 0;
	}

	if (fd < 0)
	 	error_exit(-8000, "impossible fd");
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) != 0)
		{
			line_split = ft_strsplit(line, ' ');
			if (ft_strcmp(line_split[0], "v") == 0)
			{
				t_mesh_add_point(&result, create_t_vector3(atof(line_split[1]) * size.x, atof(line_split[2]) * size.y, atof(line_split[3]) * size.z));
			}
			else if (ft_strcmp(line_split[0], "vt") == 0)
			{
				t_mesh_add_uv(&result, create_t_vector3(atof(line_split[1]), atof(line_split[2]), 0.0));
			}
			else if (ft_strcmp(line_split[0], "f") == 0)
			{
				if (ft_tablen(line_split) == 5)
				{
					// Format : 2 - 1 - 3 - 4
					i = 0;
					while (i < 4)
					{
						tab = ft_strsplit(line_split[i + 1], '/');
						index[i] = ft_atoi(tab[0]) - 1;
						if (ft_tablen(tab) >= 2 && ft_strlen(tab[1]) != 0)
							index_uv[i] = ft_atoi(tab[1]) - 1;
						i++;
					}
					set_t_face_vertices(&tmp_face, index[0], index[1], index[2]);
					set_t_face_uvs(&tmp_face, index_uv[0], index_uv[1], index_uv[2]);
					t_mesh_add_face(&result, tmp_face);

					set_t_face_vertices(&tmp_face, index[0], index[2], index[3]);
					set_t_face_uvs(&tmp_face, index_uv[0], index_uv[2], index_uv[3]);
					t_mesh_add_face(&result, tmp_face);
				}
				if (ft_tablen(line_split) == 4)
				{
					// Format : 2 - 1 - 3 - 4
					i = 0;
					while (i < 3)
					{
						tab = ft_strsplit(line_split[i + 1], '/');
						index[i] = ft_atoi(tab[0]) - 1;
						if (ft_tablen(tab) >= 2 && ft_strlen(tab[1]) != 0)
							index_uv[i] = ft_atoi(tab[1]) - 1;
						i++;
					}
					set_t_face_vertices(&tmp_face, index[0], index[1], index[2]);
					set_t_face_uvs(&tmp_face, index_uv[0], index_uv[1], index_uv[2]);
					t_mesh_add_face(&result, tmp_face);
				}
			}
		}
		free(line);
	}
	free(line);
	t_mesh_compute_normals(&result);
	close(fd);
	t_mesh_compute_bubble_box(&result);
	t_mesh_set_texture(&result, NULL);
	return(result);
}
