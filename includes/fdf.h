/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:34:43 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/04 15:38:12 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <mlx.h>
# include "get_next_line.h"

typedef struct			s_point
{
	int					valeur;
	int					x;
	int					y;
	struct s_point		*next;
}						t_point;

typedef struct			s_map
{
	int					x_max;
	int					y_max;
}						t_map;
#endif
