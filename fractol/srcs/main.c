/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:36:03 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/11 14:53:01 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		deal_key(int key, t_fract *first)
{
	(void)first;
	if (key == 53)
		exit(0);
	if (key >= 123 && key <= 126)
		translate(first, key);
	if (key == 69 || key == 78)
		zoom(first, key);
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

static void		fractol_choice(t_fract *first, char **av)
{
	int		i;
	t_fract	*tmp;

	i = 1;
	tmp = first;
	while (tmp)
	{
		if (!ft_strcmp("Mandelbrot", av[i]))
			first->type = 1;
		else if (!ft_strcmp("Julia", av[i]))
			first->type = 2;
		else if (!ft_strcmp("Autre", av[i]))
			first->type = 3;
		else
			error(3);
		i++;
		tmp = tmp->next;
	}
}

void			fractol(t_fract *first)
{
	t_fract	*tmp;

	tmp = first;
	while (tmp)
	{
		open_windows(first);
		if (first->type == 1)
			Mandelbrot(first);
		else if (first->type == 2)
			Julia(first);
		/*else
			autre(first);*/
		tmp = tmp->next;
	}
}

int				main(int ac, char **av)
{
	t_fract	*first;

	if (ac == 0)
		error(1);
	if (!init_fract(&first))
		error(2);
	fractol_choice(first, av);
	fractol(first);
	mlx_hook(first->win, 2, (1L << 1), deal_key, first);
	mlx_loop(first->ptr);
	return (0);
}
