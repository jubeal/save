/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:15:10 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 16:15:11 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

void		ft_bzero(void *src, size_t nb_bytes)
{
	char	*p_src;
	size_t	i;

	i = 0;
	p_src = src;
	while (nb_bytes > i)
	{
		p_src[i] = 0;
		i++;
	}
}
