/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:17:13 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/03 11:45:49 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	char c = 'A';
	char c1 = 'A';
	
	printf("User:   %c\n", ft_tolower(c));
	printf("System: %c\n", tolower(c1));
	return (0);
}
*/