/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:37 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 12:44:20 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s || !f)
		return (NULL);
	i = 0;
	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (*(s + i) != '\0')
	{
		str[i] = f(i, *(s + i));
		i++;
	}
	str[i] = '\0';
	return (str);
}
