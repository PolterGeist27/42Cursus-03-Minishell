/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:18:37 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/26 16:27:18 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_whitespaces(char *str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	result = (char *)malloc(sizeof(char) * (ft_meta_strlen(str) + 1));
	while (str[i])
	{
		if (ft_strrchr("\"\'", str[i]) && !quote)
			quote = str[i];
		else if (ft_strrchr("\"\'", str[i]) && quote == str[i])
			quote = 0;
		if (!quote && ft_strchr(REDIR, str[i]))
		{
			result[j++] = ' ';
			result[j++] = str[i++];
			if (str[i] == str[i - 1])
				result[j++] = str[i++];
			result[j++] = ' ';
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
