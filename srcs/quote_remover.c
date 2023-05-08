/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:20:28 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/08 14:00:06 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	length_no_quotes(char *arg)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i])
	{
		if (ft_strchr("\"\'", arg[i]) && !quote)
		{
			quote = arg[i];
			len--;
		}
		else if (ft_strchr("\"\'", arg[i]) && quote == arg[i])
		{
			len--;
			quote = 0;
		}
		len++;
	}
	return (len);
}

static void	quote_checker(char *arg, int *i, char *quote)
{
	if (ft_strrchr("\"\'", arg[*i]) && !*quote)
	{
		*quote = arg[*i];
	}
	else if (ft_strrchr("\"\'", arg[*i]) && *quote == arg[*i])
	{
		*quote = 0;
	}
}

char	*remove_quotes(char *arg)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	i = -1;
	j = 0;
	quote = 0;
	if (length_no_quotes(arg) == 0)
	{
		free(arg);
		return (ft_strdup(""));
	}
	result = (char *)malloc(sizeof(char) * (length_no_quotes(arg) + 1));
	while (arg[++i])
	{
		quote_checker(arg, &i, &quote);
		if (i > (int)ft_strlen(arg) - 1)
			break ;
		if ((quote && quote != arg[i]) || (!quote && !ft_strchr("\"\'", arg[i])))
			result[j++] = arg[i];
	}
	return (result[j] = 0, free(arg), result);
}
