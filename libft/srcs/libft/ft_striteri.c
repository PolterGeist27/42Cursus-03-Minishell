/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:09:54 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/11 12:14:37 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s || !f)
		return ;
	len = ft_strlen(s);
	while (i < len)
	{
		(*f)(i, &s[i]);
		i += 1;
	}
}
