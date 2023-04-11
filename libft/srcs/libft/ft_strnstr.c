/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:52:20 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/07 15:15:03 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*little))
		return ((char *)big);
	i = 0;
	j = 0;
	while (i < len && *(big + i) != '\0')
	{
		while (*(big + i + j) == *(little + j)
			&& *(little + j) != '\0' && *(big + i + j) != '\0' && i + j < len)
			j++;
		if (*(little + j) == '\0')
			return ((char *)(big + i));
		j = 0;
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*big = "lorem ipsum dolor sit amet";
	char	*little = "a";

	printf("User:\n");
	printf("Big: %s | Little: %s\n Result: %s\n\n", big, 
	little, ft_strnstr(big, little, 15));
	printf("System:\n");
	printf("Big: %s | Little: %s\n Result: %s\n", big, little, strstr(big, little));
}
*/