/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:47:42 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/01 15:04:21 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_env(t_minishell *mini, char *info)
{
	int		size;
	char	*name;

	size = 0;
	while (info[size] != '=')
		size++;
	name = ft_substr(info, 0, size);
	modify_info(mini->env, name, info);
	free(name);
}

int	check_validity(char *str)
{
	int		i;
	int		size;
	char	*name;

	size = 0;
	i = 0;
	while (str[size] != '=')
		size++;
	name = ft_substr(str, 0, size);
	while (name[i])
	{
		if (!isalnumextra(name[i]))
		{
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

void	check_export(t_minishell *mini, char **cmd_args)
{
	int		status;
	int		i;

	i = 0;
	while (cmd_args[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status != 2)
	{
		if (i > 1)
		{
			i = 0;
			g_exit_status = 0;
			while (cmd_args[++i])
			{
				if (check_validity(cmd_args[i]))
					change_env(mini, cmd_args[i]);
			}
		}
	}
}
