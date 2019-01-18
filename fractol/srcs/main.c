/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:36:03 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/18 16:37:33 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		deal_key(int key, t_fract *first)
{
	if (key == 53)
		end_program(first);
	if (key >= 123 && key <= 126)
		translate(first, key);
	if (key == 69 || key == 78)
		zoom(key, first);
	if (key == 46 && first->tools->mouse_stop)
		first->tools->mouse_stop = 0;
	else if (key == 46 && !first->tools->mouse_stop)
		first->tools->mouse_stop = 1;
	if (key == 15)
	{
		free(first->tools);
		first->tools = NULL;
		fractol(first);
	}
	return (1);
}

void			error(int n)
{
	if (n == 1)
		ft_putstr("usage: ./fractol fractol_type\n");
	if (n == 2)
		ft_putstr("error\n");
	if (n == 3)
		ft_putstr("error: unknown fractol_type. Enter ./fractol ?\n");
	exit(0);
}

void			fractol_choice(t_fract *first)
{

	if (!ft_strcmp("Mandelbrot", first->av[first->i]))
		first->type = 1;
	else if (!ft_strcmp("Julia", first->av[first->i]))
		first->type = 2;
	else if (!ft_strcmp("Julia_2", first->av[first->i]))
		first->type = 3;
	else
		error(3);
}

void			fractol(t_fract *first)
{
		if (first->type == 1)
			Mandelbrot(first);
		else if (first->type == 2)
			Julia(first);
		else if (first->type == 3)
			Julia_2(first);
}

int				main(int ac, char **av)
{
	t_fract	*first;

	if (ac == 1)
		error(1);
	if (!init_fract(&first, av))
		error(2);
	fractol_choice(first);
	open_windows(first);
	fractol(first);
	mlx_hook(first->win, 2, (1L << 1), deal_key, first);
	mlx_mouse_hook(first->win, zoom, first);
	mlx_hook(first->win, 6, 1L << 6, mouse_move_hook, first);
	mlx_loop(first->ptr);
	return (0);
}
