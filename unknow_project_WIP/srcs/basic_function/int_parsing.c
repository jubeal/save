/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:14:03 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 16:14:04 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int		ft_atoi(const char *str)
{
	int			i;
	long long	number;
	int			neg;

	i = 0;
	number = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * neg);
}

int		get_short(int a, int b, int c)
{
	int			result;

	result = a;
	if (result > b)
		result = b;
	if (result > c)
		result = c;
	return (result);
}

int		get_big(int a, int b, int c)
{
	int			result;

	result = a;
	if (result < b)
		result = b;
	if (result < c)
		result = c;
	return (result);
}

int		min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int		max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}
