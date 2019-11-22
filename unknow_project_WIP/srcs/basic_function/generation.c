/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:50:52 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 16:18:46 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int		generate_nbr(int min, int max)
{
	int	value;
	int	tmp;

	if (min < 0)
		max += -min;
	value = rand();
	value = value % max;
	value += min;
	return (value);
}
