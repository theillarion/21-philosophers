#include "header.h"

typedef unsigned char	t_uchar;

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char	*str1, const char	*str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n && (str1[i] || str2[i]))
	{
		if ((t_uchar)str1[i] != (t_uchar)str2[i])
			return ((t_uchar)str1[i] - (t_uchar)str2[i]);
		i++;
	}
	return (0);
}
