/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hexastr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:52:27 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/20 15:50:37 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_get_hexastr(unsigned long long nb, char *base)
{
	int		nb_length;
	char	*hexastr;

	nb_length = ft_getlength(nb, 16);
	hexastr = (char *)malloc(sizeof(char) * (nb_length + 1));
	if (!hexastr)
		return (0);
	hexastr[nb_length] = '\0';
	while (nb_length > 0)
	{
		hexastr[nb_length - 1] = base[nb % 16];
		nb /= 16;
		nb_length--;
	}
	return (hexastr);
}
