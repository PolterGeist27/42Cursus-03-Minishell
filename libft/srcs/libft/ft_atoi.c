/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:47:19 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:20:56 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			h;
	long int	final;

	i = 0;
	j = 0;
	final = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			j++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		h = str[i] - 48;
		final = (final * 10) + h;
		i++;
	}
	if (j % 2 == 1)
		final *= -1;
	return (final);
}

/*
#include <stdio.h>
#include <stdlib.h>
int		main(void)
{
	char	str[256] = "2147483648";

	printf("minha: 	  %d\n", ft_atoi(str));
	printf("original: %d\n", atoi(str));
}
*/
