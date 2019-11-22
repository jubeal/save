/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:18:14 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 17:07:37 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (i < ft_tablen(tab))
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strjoinf(char *s1, char *s2, int c)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (c == 1 || c == 3)
		free(s1);
	if (c == 2 || c == 3)
		free(s2);
	return (str);
}
