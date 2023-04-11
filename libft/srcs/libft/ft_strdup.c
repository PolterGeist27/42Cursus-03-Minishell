/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:53:56 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 11:45:49 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*dest;

	i = ft_strlen(s) + 1;
	j = 0;
	dest = malloc(i * sizeof(char));
	if (!dest)
		return (0);
	while (s[j] != '\0')
	{
		dest[j] = s[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
	free(dest);
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

int	main(void)
{
	char *test;
	char *dup;
	test = "Hello World!";
	printf("test = %s	|	size: %d\n", test, ft_strlen(test));
	dup = ft_strdup(test);
	printf("dup  = %s	|	size: %d\n", dup, ft_strlen(dup));
	free(dup);
}
*/