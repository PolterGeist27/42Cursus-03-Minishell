/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:11:14 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/03 11:38:36 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	char c = 'a';
	char c1 = 'a';
	
	printf("User:   %c\n", ft_toupper(c));
	printf("System: %c\n", toupper(c1));
	return (0);
}
*/