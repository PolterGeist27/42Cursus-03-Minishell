/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:17:19 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/11 12:53:15 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_declare(char *str)
{
	int		size;
	char	*name;
	char	*info;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	if (str[size] != '=')
	{
		info = ft_strjoin("declare -x ", str);
		return (info);
	}
	name = ft_substr(str, 0, size);
	info = ft_strjoin(name, "=\"");
	free(name);
	name = ft_strjoin(info, str + size + 1);
	free(info);
	info = ft_strjoin(name, "\"");
	free(name);
	name = ft_strjoin("declare -x ", info);
	free(info);
	return (name);
}

static void	export_error(t_minishell *mini, char **cmd_args)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	while (cmd_args[i])
	{
		if (!check_validity(cmd_args[i]))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd_args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit(1);
		}
		i++;
	}
	free_child(mini, cmd_args, 0);
	exit(0);
}

static void	sort_env(char **env)
{
	int		n;
	int		i;
	int		j;
	char	*temp;

	n = 0;
	i = 1;
	while (env[n])
		n++;
	while (i < n)
	{
		j = i -1;
		temp = env[i];
		while (j >= 0 && ft_strncmp(env[j], temp, ft_strlen(env[j])) > 0)
		{
			env[j + 1] = env[j];
			j--;
		}
		env[j + 1] = temp;
		i++;
	}
}

static void	export_print(t_minishell *mini, char **cmd_args)
{
	char	**env;
	int		j;

	env = convert_export(mini);
	sort_env(env);
	j = 0;
	while (env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}
	ft_free_split(env);
	free_child(mini, cmd_args, 0);
	exit(0);
}

void	builtin_export(t_minishell *mini, char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i])
		i++;
	if (i == 1)
		export_print(mini, cmd_args);
	else if (i > 1)
	{
		if (cmd_args[1][0] == '-')
		{
			ft_putstr_fd("minishell: export: no options supported\n", 2);
			free_child(mini, cmd_args, 0);
			exit (2);
		}
		else
			export_error(mini, cmd_args);
	}
}
