/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:17:58 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/08 16:48:49 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
# define WIN_X 540
# define WIN_Y 480

typedef struct		s_fract
{
	int				type;
	int				x;
	int				y;
	void			*ptr;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	struct s_fract	*next;
}					t_fract;

typedef struct		s_maths
{
	int				iter_max;
	long double		cr;
	long double		ci;
	float			zr;
	float			zi;
	int				i;
	float			zoomx;
	float			zoomy;
	float			x1;
	float			x2;
	float			y1;
	float			y2;
}					t_maths;

void				Mandelbrot(t_fract *first);
int					init_fract(t_fract **first);
void				open_windows(t_fract *first);
void				init_maths(t_maths **tools);
void				pixel_put_img(int x, int y, t_fract *curent, int color);
#endif
