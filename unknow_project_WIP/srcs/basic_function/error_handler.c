/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:37:21 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 15:37:22 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

void	error_exit(int error, char *message)
{
	ft_putstr("Error ");
	ft_putnbr(error);
	ft_putstr(" : ");
	ft_putstr(message);
	endl();
	exit(error);
}
