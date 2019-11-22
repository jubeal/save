/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:09:04 by adjouber          #+#    #+#             */
/*   Updated: 2019/11/05 16:46:35 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int		is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

float	ft_atof_bis(float a, int e)
{
	float	ret;

	while (e > 0)
	{
		a *= 10.0;
		e--;
	}
	while (e < 0)
	{
		a *= 0.1;
		e++;
	}
	ret = a;
	return (ret);
}

float	ft_atof(char *s)
{
	float	a;
	int		neg;
	int		e;
	int		c;
	int		i;

	a = 0.0;
	neg = 1;
	e = 0;
	if (s[0] == '-')
	{
		neg = -1;
		s++;
	}
	while ((c = *s++) != '\0' && is_digit(c))
		a = a * 10.0 + (c - '0');
	if (c == '.')
		while ((c = *s++) != '\0' && is_digit(c))
		{
			a = a * 10.0 + (c - '0');
			e = e - 1;
		}
	a = ft_atof_bis(a, e);
	return (a * neg);
}
