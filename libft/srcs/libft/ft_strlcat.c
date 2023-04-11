/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:09:17 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 15:56:26 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	final;

	if (size == 0 || size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	else
		final = ft_strlen(src) + ft_strlen(dst);
	j = 0;
	while (dst[j])
		j++;
	i = 0;
	while (j + 1 < size && src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (final);
}

/*
#include <stdio.h>
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// Original strlcat from the github of the creator,
// so I can compare the outputs

size_t	strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	// Find the end of dst and adjust bytes left but don't go past end
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + ft_strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	// count does not include NUL
}

int main(void)
{
	char	*dest = NULL;
	char	*src = "nyan !";
	// Another set of variables 
	// so that the input of the second function 
	// isnt the output of the first one
	char	*dest1 = NULL;
	char	*src1 = "nyan !";
	// Size of the final string (length of dest + src)
	size_t	n = 0;

	printf("User:  \n	String: %s	|	size: %d\n", dest, ft_strlcat(dest, src, n));
	printf("System:\n	String: %s	|	size: %d\n", dest1, strlcat(dest1, src1, n));
	return (0);
}
*/