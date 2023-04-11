/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:10:42 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/27 14:25:57 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(s + i) != '\0')
	{
		while (*(s + i) == c && *(s + i) != '\0')
			i++;
		if (*(s + i) != '\0')
		{
			count++;
			i++;
		}
		while (*(s + i) != c && *(s + i) != '\0')
			i++;
	}
	return (count);
}

static int	ft_wordlen(char const *s, char c, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (*(s + i) && (*(s + i) != c))
	{
		count++;
		i++;
	}
	return (i);
}

static char	*ft_getword(char const *s, char c, int start)
{
	char	*word;
	int		len;
	int		i;
	int		j;

	i = start;
	j = 0;
	len = ft_wordlen(s, c, start);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (*(s + i) == c)
		i++;
	while (*(s + i) != c && *(s + i) != '\0')
	{
		word[j] = *(s + i);
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*(s + i) != '\0')
	{
		while (*(s + i) == c && *(s + i) != '\0')
			i++;
		if (*(s + i) != '\0')
		{
			arr[j++] = ft_getword(s, c, i++);
		}
		while (*(s + i) != c && *(s + i) != '\0')
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

/*
#include <stdio.h>

int	main()
{
	int		index;
	char	c = ' ';
	char	*str = "Ola tudo bem";
	char	**split;
	split = ft_split(str, c);
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
}
*/