/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:33:33 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/27 14:49:05 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[30] = "Hello World!";
	printf("User: %d\n", ft_strlen(str));
	printf("System: %d\n", strlen(str));
	return (0);	
}
*/