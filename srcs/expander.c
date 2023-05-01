/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:26:25 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/01 10:26:23 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	total_length2(char *arg, int *i, int *len, t_minishell *mini)
{
	int		j;
	char	*temp;
	char	*value;

	j = 0;
	if (arg[*i + 1] != '?')
	{
		while (isalnumextra(arg[*i + 1 + j]))
			j++;
		temp = ft_substr(arg, *i + 1, j);
		value = get_info_env(&mini->env, temp);
		if (value)
			*len += ft_strlen(value);
		free(temp);
		*i += j;
	}
	else
	{
		temp = ft_itoa(g_exit_status);
		len += ft_strlen(temp);
		free(temp);
		*i += 1;
	}
}

static int	total_length(char *arg, t_minishell *mini)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i])
	{
		quote = quote_value(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			total_length2(arg, &i, &len, mini);
		else
			len++;
	}
	return (len);
}

static void	expand_exit_status(char *result, t_minishell *mini, int *i)
{
	int		k;
	char	*value;

	value = ft_itoa(g_exit_status);
	k = -1;
	while (value[++k])
		result[mini->counter++] = value[k];
	free(value);
	*i += 1;
}

static void	expand_variable(char *arg, char *result, int *i, t_minishell *mini)
{
	char	*temp;
	char	*value;
	int		len;
	int		k;

	if (arg[*i + 1] != '?')
	{
		len = 0;
		while (isalnumextra(arg[*i + 1 + len]))
			len++;
		temp = ft_substr(arg, *i + 1, len);
		value = get_info_env(&mini->env, temp);
		free(temp);
		*i += len;
		if (value)
		{
			k = -1;
			while (value[++k])
				result[mini->counter++] = value[k];
		}
	}
	else
		expand_exit_status(result, mini, i);
}

char	*expander(char *arg, t_minishell *mini)
{
	char	*result;
	char	quote;
	int		i;

	i = -1;
	mini->counter = 0;
	quote = 0;
	result = (char *)malloc(sizeof(char) * (total_length(arg, mini) + 1));
	while (arg[++i])
	{
		quote = quote_value(arg[i], quote);
		if (arg[i] == '$' && quote != '\'')
			expand_variable(arg, result, &i, mini);
		else
			result[mini->counter++] = arg[i];
	}
	result[mini->counter] = 0;
	free(arg);
	return (result);
}
