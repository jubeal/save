/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:56:57 by jubeal            #+#    #+#             */
/*   Updated: 2018/12/04 15:09:42 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"
#include "libft.h"

int		deal_key(int key, void *param)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		main(int ac, char **av)
{
	//void		*ptr;
	//void		*win;
	int			i;
	t_point		*map;

	if (ac != 2)
		return (1);
	i = -1;
	if (!(map = (t_point *)malloc(sizeof(t_point))))
		return (1);
	file_reader
	/*ptr = mlx_init();
	win = mlx_new_window(ptr, 560, 480, "test pixel");
	mlx_key_hook(win, deal_key, (void *)0);
	mlx_loop(ptr);*/
	return (0);
}
