/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:46:21 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/28 12:40:19 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int get_num_vars(char *cmd)
{
	int 	i;
	int 	num_vars;

	i = 0;
	num_vars = 0;
	while (cmd[i] != '\0')
	{
			if (cmd[i] == '$' && cmd[i + 1] != '\0' && cmd[i + 1] != '?')
				num_vars++;
		i++;
	}
	return (num_vars);
}

static char	**get_var_names(char *cmd)
{
	char	**var_names;
	int 	i;
	int 	k;
	int		len;
	int 	num_vars;

	i = 0;
	len = 0;
	k = 0;
	num_vars = get_num_vars(cmd);
	var_names = (char **)malloc(sizeof(char *) * (num_vars + 1));
	var_names[num_vars] = NULL;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$' && cmd[i + 1] != '\0' && cmd[i + 1] != '?')
		{
			i++;
			while (ft_isalnum(cmd[i + len]))
				len++;
			var_names[k] = malloc(sizeof(char) * len + 1);
			ft_strlcpy(var_names[k], &cmd[i], len + 1);
			k++;
			len = 0;
		}
		i++;
	}
	return (var_names);
}

static int	get_full_length(char *cmd, char **var_names)
{
	int len;
	int var_name_len;
	int i;

	len = 0;
	i = 0;
	var_name_len = 0;
	while (cmd[i++] != '\0')
	{
		if (cmd[i] == '$' && (cmd[i + 1] != '\0' && cmd[i + 1] != '?'))
		{
			while (ft_isalnum(cmd[i + var_name_len]))
				var_name_len++;
			len -= var_name_len + 1;
			var_name_len = 0;
		}
		len++;
	}
	i = 0;
	while (var_names[i] != NULL)
		len += (int)ft_strlen(var_names[i++]);
	return (len);
}

char	*expander(char *cmd, t_list **env)
{
	char	**var_names;
	char	*result;
	char 	*tmp;
	int 	i;
	int 	j;
	int 	k;
	int 	h;

	i = 0;
	j = 0;
	k = 0;
	h = 0;
	var_names = get_var_names(cmd);
	result = (char *)malloc(sizeof(char) * (get_full_length(cmd, var_names) + 1));
	while (cmd[i] != '\0')
	{
		if (cmd[i++] == '$' && (cmd[i + 1] != '\0' && cmd[i + 1] != '?'))
		{
			while (ft_isalnum(cmd[i]))
				i++;
			tmp = ft_strdup(get_info_env(env, var_names[j++]));
			while (tmp[h] != '\0')
				result[k++] = tmp[h++];
			h = 0;
		}
    else
		  result[k++] = cmd[i++];
	}
  free(cmd);
	return(result[k] = '\0', result);
}
