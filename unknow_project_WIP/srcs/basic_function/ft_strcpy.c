#include "unknow_project.h"

char	*ft_strcpy(char *dest, const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}