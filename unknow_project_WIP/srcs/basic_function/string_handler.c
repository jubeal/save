#include "unknow_project.h"

char		*ft_strnew(int size)
{
	char	*ret;
	int		i;

	ret = NULL;
	if (!(ret = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	// printf("malloc strnew\n");
	i = 0;
	while (i <= size)
	{
		ret[i] = '\0';
		i++;
	}
	return (ret);
}

int			ft_strlen(char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(char *src)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_strnew(ft_strlen(src));
	while (src[i] != '\0')
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char		*ft_strjoin(char *src1, char *src2)
{
	char	*ret;
	int 	i;
	int		j;

	ret = ft_strnew(ft_strlen(src1) + ft_strlen(src2));
	i = 0;
	while (i < ft_strlen(src1))
	{
		ret[i] = src1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(src2))
	{
		ret[i + j] = src2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

void		ft_stradd(char **src1, char *src2)
{
	if (*src1 == NULL)
		*src1 = ft_strdup(src2);
	else if (src2 != NULL)
		*src1 = ft_strjoin(*src1, src2);
}
