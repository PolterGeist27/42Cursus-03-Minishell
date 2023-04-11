/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:58:22 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 14:25:57 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	i = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[i]) && i != 0)
		i--;
	return (ft_substr(s1, 0, i + 1));
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr || !s)
		return (0);
	i = 0;
	while (len > i && *(s + start + i) != '\0' && start < ft_strlen((char *)s))
	{
		ptr[i] = *(s + start + i);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	main()
{
	char	*s1 = "";
	char	*set = " \n\t";

	printf("%s\n", ft_strtrim(s1, set));

	printf("s1: %s	|	size: %d	|	set: %s\n \
	Result: %s	|	Size: %d\n", s1, ft_strlen(s1), set, \
	ft_strtrim(s1, set), ft_strlen(ft_strtrim(s1, set)));
}
*/