/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:41 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/10 11:33:20 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
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

// Original strlcpy from the github of the creator,
// so I can compare the outputs

size_t  strlcpy(char * dst, const char * src, size_t dsize)
{
    const char *osrc = src;
    size_t nleft = dsize;

    // Copy as many bytes as will fit.
    if (nleft != 0) {
        while (--nleft != 0) {
            if ((*dst++ = *src++) == '\0')
                break;
        }
    }

    // Not enough room in dst, add NUL and traverse rest of src.
    if (nleft == 0) {
        if (dsize != 0)
            *dst = '\0';        // NUL-terminate dst
        while (*src++)
            ;
    }

    return(src - osrc - 1);    // count does not include NUL
}

int main(void)
{
	char	*dest = NULL;
	char	*src = NULL;
	// Another set of variables 
	// so that the input of the second function 
	// isnt the output of the first one
	char	*dest1 = NULL;
	char	*src1 = NULL;
	// Size of the pretended destination string (with null)
	size_t	n = 10;

	printf("User:  \n	String: %s	|	size: %d\n", dest, ft_strlcpy(dest, src, n));
	//printf("System:\n	String: %s	|	size: %d\n", dest1, strlcpy(dest1, src1, n));
	return (0);
}
*/