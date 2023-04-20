/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/20 15:50:37 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
