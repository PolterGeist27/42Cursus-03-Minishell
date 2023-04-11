/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:35:34 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:22:45 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennbr(long n, int sign)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (sign == -1)
		len++;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_putnbr(char *str, int len, long n)
{
	while (n > 0)
	{
		str[len--] = 48 + (n % 10);
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(long n)
{
	int		sign;
	int		len;
	char	*str;

	sign = 1;
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	len = ft_lennbr(n, sign);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (sign == -1)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	str = ft_putnbr(str, len, n);
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	//printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(-9));
	//printf("%s\n", ft_itoa(2147483647));
}
*/
