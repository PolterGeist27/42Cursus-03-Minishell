/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:18:50 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/30 18:57:51 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_args(char **cmd_args, t_minishell *mini)
{
	int	i;

	i = -1;
	while (cmd_args[++i])
		if (ft_strrchr(cmd_args[i], '$'))
			cmd_args[i] = expander(cmd_args[i], mini);
	i = -1;
	while (cmd_args[++i])
		if (ft_strrchr(cmd_args[i], '\'') || ft_strrchr(cmd_args[i], '\"'))
			cmd_args[i] = remove_quotes(cmd_args[i]);
}

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
		quote = quote_value(str[i], quote);
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

size_t	ft_meta_strlen(char *str)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strchr(REDIR, str[i]))
		{
			len += 3;
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}
