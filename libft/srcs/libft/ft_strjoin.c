/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:32:05 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 16:00:37 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcpy((str + ft_strlen(s1)), s2, ft_strlen(s2) + 1);
	return (str);
}

/*
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

int	main()
{
	char	*s1 = "Hello ";
	char	*s2 = "World!";

	printf("s1: %s	|	s2: %s\n
	Result: %s	|	Size: %d\n", s1, s2,
	 ft_strjoin(s1, s2), ft_strlen(ft_strjoin(s1, s2)));
}
*/