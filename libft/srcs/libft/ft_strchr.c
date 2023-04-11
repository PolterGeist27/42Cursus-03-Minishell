/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:42:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/27 14:45:54 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[25] = "Ola seu camelo!";
	char	c = 'c';

	// Function I created
	printf("User:\n		String: %s	| Char: %c\n", str, c);
	printf("		Pointer: %p | Value: %s\n", ft_strchr(str, c), ft_strchr(str, c));
	
	// Function from string.h library
	printf("System:\n		String: %s	| Char: %c\n", str, c);
	printf("		Pointer: %p | Value: %s\n", strchr(str, c), strchr(str, c));
	return (0);
}
*/