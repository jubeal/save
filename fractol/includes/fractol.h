/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:17:58 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/11 14:53:18 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
# define WIN_X 540
# define WIN_Y 480

typedef struct		s_maths
{
	long double		iter_max;
	long double		cr;
	long double		ci;
	long double		zr;
	long double		zi;
	int				i;
	long double		zoomx;
	long double		zoomy;
	int				x;
	int				y;
	long double		x1;
	long double		x2;
	long double		y1;
	long double		y2;
}					t_maths;

typedef struct		s_fract
{
	int				type;
	int				win_x;
	int				win_y;
	void			*ptr;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	struct s_fract	*next;
	int				color_value;
	int				r;
	int				g;
	int				b;
	t_maths			*tools;
}					t_fract;

void				Mandelbrot(t_fract *first);
int					init_fract(t_fract **first);
void				open_windows(t_fract *first);
void				init_maths(t_maths **tools, t_fract *first);
void				pixel_put_img(int x, int y, t_fract *curent, int color);
int					set_color(t_maths *tools, t_fract *first);
void				translate(t_fract *first, int key);
void				fractol(t_fract *first);
void				zoom(t_fract *first, int key);
void				Julia(t_fract *first);
void				Buddhabrot(t_fract *first);
#endif
