/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 14:31:58 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_putaddress(unsigned long nb)
{
	int	count;

	count = 0;
	if (!nb)
		return (ft_putstr("(nil)"));
	else
		write (1, "0x", 2);
	count += ft_puthexa(nb, 'x');
	return (count + 2);
}
