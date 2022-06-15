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

char	*ft_strjoin(const char	*str1, const char	*str2)
{
	size_t	i;
	size_t	length_str1;
	size_t	length_str2;
	char	*new_str;

	if ((str1 == NULL && str2 == NULL))
		return (NULL);
	length_str1 = ft_strlen(str1);
	length_str2 = ft_strlen(str2);
	new_str = (char *)malloc((length_str1 + length_str2 + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < length_str1 && str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	while (i < length_str1 + length_str2 && str2[i - length_str1])
	{
		new_str[i] = str2[i - length_str1];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strdup(const char	*str)
{
	size_t	i;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
