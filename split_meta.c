/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:28:52 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/26 08:31:16 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordcount_meta(char *str, char c)
{
	int		i;
	int		wordcount;
	char	quote;

	i = 0;
	wordcount = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wordcount++;
		while (str[i] && str[i] != c || quote)
		{
			if (ft_strrchr("\"\'", str[i]) && !quote)
				quote = str[i];
			else if (ft_strrchr("\"\'", str[i]) && quote == str[i])
				quote = 0;
			i++;
		}
	}
	return (wordcount);
}

static int	ft_wordlen(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && str[i] != c || quote)
	{
		if (ft_strrchr("\"\'", str[i]) && !quote)
			quote = str[i];
		else if (ft_strrchr("\"\'", str[i]) && quote == str[i])
			quote = 0;
		i++;
	}
	return (i);
}

static char	*get_word(char *s, char c, char **words, int j)
{
	char	quote;

	quote = 0;
	words[j] = ft_substr(s, 0, ft_wordlen(s, c));
	while (*s && *s != c || quote)
	{
		if (ft_strrchr("\"\'", *s) && !quote)
			quote = *s;
		else if (ft_strrchr("\"\'", *s) && quote == *s)
			quote = 0;
		s++;
	}
	return (s);
}

char	**split_meta(char *s, char c)
{
	char	**words;
	int		wdcount;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	words = malloc(sizeof(char *) * (ft_wordcount_meta(s, c) + 1));
	if (!words)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			s = get_word(s, c, words, j);
		j++;
	}
	words[j] = 0;
	return (words);
}
