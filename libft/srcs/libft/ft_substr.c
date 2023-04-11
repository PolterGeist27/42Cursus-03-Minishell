/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:17:03 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 12:01:24 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr || !s)
		return (0);
	i = 0;
	while (len > i && *(s + start + i) != '\0' && start < ft_strlen((char *)s))
	{
		ptr[i] = *(s + start + i);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include <stdio.h>

int	main()
{
	char	*str = "i just want this part #############";
	int		i = 5;
	size_t	len = 10;

	printf("String: %s	|	Start: %d\nResult: %s\n", str, i, ft_substr(str, i, len));
}
*/