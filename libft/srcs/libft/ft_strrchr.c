/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:43:51 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/07 11:58:05 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*ptr;

	i = ft_strlen(s);
	ptr = &s[i];
	while (i >= 0)
	{
		if (*ptr == c)
			return ((char *)ptr);
		ptr--;
		i--;
	}
	if (c == '\0')
		return ((char *)ptr);
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(void)
{
	char	str[25] = "Ola seu camelo!";
	char	c = 'O';

	// Function I created
	printf("User:\n		String: %s	| Char: %c\n", str, c);
	printf("		Pointer: %p | Value: %s\n", ft_strrchr(str, c), ft_strrchr(str, c));
	
	// Function from string.h library
	printf("System:\n		String: %s	| Char: %c\n", str, c);
	printf("		Pointer: %p | Value: %s\n", strrchr(str, c), strrchr(str, c));
	return (0);
}
*/