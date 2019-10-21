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
