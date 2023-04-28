/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:26:25 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 17:34:08 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	isalnumextra(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
		return (1);
	else
		return (0);
}

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
	/* else
	{
		temp = ft_itoa(exit_status);
		len += ft_strlen(temp);
		free(temp);
		*i++;
	} */
}

static int total_length(char *arg, t_minishell *mini)
{
    int 	i;
    int 	len;
    char    quote;

    i = -1;
    len = 0;
    quote = 0;
    while(arg[++i])
    {
        quote = quote_value(arg[i], quote);
        if (arg[i] == '$' && quote != '\'')
			total_length2(arg, &i, &len, mini);
        else
            len++;
    }
    return (len);
}

/* void    expand_variable(char *arg, char *result, int *i, t_minishell *mini)
{
	char	*temp;
	char	*value;
	int     len;
	int     k;

	len = 0;
	while (isalnumextra(arg[i + 1 + len]))
		len++;
	temp = ft_substr(arg, i + 1, len);
	value = get_info_env(&mini->env, temp);
	free(temp);
	i += len;
	if (value)
	{
		k = -1;
		while (value[++k])
		{
			result[j] = value[k];
			j++;
		}
	}

	}
 */

char    *expander(char *arg, t_minishell *mini)
{
    char    *result;
    char    quote;
    char    *temp;
    char    *value;
    int     i;
    int     j;
    int     k;
    int     len;

    i = -1;
    j = 0;
    k = 0;
    quote = 0;
    result = (char *)malloc(sizeof(char) * (total_length(arg, mini) + 1));
    while(arg[++i])
    {
        quote = quote_value(arg[i], quote);
        if (arg[i] == '$' && arg[i + 1] != '?' && quote != '\'')
        {
            len = 0;
            while (isalnumextra(arg[i + 1 + len]))
                len++;
            temp = ft_substr(arg, i + 1, len);
            value = get_info_env(&mini->env, temp);
            free(temp);
            i += len;
            if (value)
            {
                k = -1;
                while (value[++k])
                {
                    result[j] = value[k];
                    j++;
                }
            }
        }
        /* else if (arg[i] == '$' && arg[i + 1] == '?' && quote != '\'')
        {
            len = 0;
            value = ft_itoa(exit_status);
            k = -1;
            while (value[++k])
            {
                result[j] = value[k];
                j++;
            }
            free(value);
        } */
        else
        {
            result[j] = arg[i];
            j++;
        }
    }
    result[j] = 0;
    free(arg);
    return (result);
}
