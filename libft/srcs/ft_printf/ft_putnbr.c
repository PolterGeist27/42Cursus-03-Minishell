/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 14:32:06 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_putnbr(long long nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789";
	if (nb < 0)
	{
		nb *= -1;
		count += ft_putchar('-');
	}
	if (nb < 10)
	{
		count += ft_putchar(base[nb]);
	}
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	return (count);
}
