/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:20:07 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/04 12:52:38 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *name)
{
	if (ft_strlen(name) == 4 && !ft_strncmp(name, "echo", 4))
		return (1);
	if (ft_strlen(name) == 2 && !ft_strncmp(name, "cd", 2))
		return (2);
	if (ft_strlen(name) == 3 && !ft_strncmp(name, "pwd", 3))
		return (1);
	if (ft_strlen(name) == 6 && !ft_strncmp(name, "export", 6))
		return (3);
	if (ft_strlen(name) == 5 && !ft_strncmp(name, "unset", 5))
		return (4);
	if (ft_strlen(name) == 3 && !ft_strncmp(name, "env", 3))
		return (1);
	if (ft_strlen(name) == 4 && !ft_strncmp(name, "exit", 4))
		return (5);
	return (0);
}

void	check_builtin(t_minishell *mini, char **cmd_args)
{
	if (!cmd_args[0])
		return ;
	expand_args(cmd_args, mini);
	if (is_builtin(cmd_args[0]) == 2)
		check_cd(mini, cmd_args);
	else if (is_builtin(cmd_args[0]) == 3)
		check_export(mini, cmd_args);
	else if (is_builtin(cmd_args[0]) == 4)
		check_unset(mini, cmd_args);
	else if (is_builtin(cmd_args[0]) == 5)
		check_exit(mini, cmd_args);
}

void	execute_builtin(t_minishell *mini, char **cmd_args, int i)
{
	if (ft_strlen(cmd_args[0]) == 4 && !ft_strncmp(cmd_args[0], "echo", 4))
		builtin_echo(mini, cmd_args);
	if (ft_strlen(cmd_args[0]) == 2 && !ft_strncmp(cmd_args[0], "cd", 2))
		builtin_cd(mini, cmd_args);
	if (ft_strlen(cmd_args[0]) == 3 && !ft_strncmp(cmd_args[0], "pwd", 3))
		builtin_pwd(mini, cmd_args);
	if (ft_strlen(cmd_args[0]) == 6 && !ft_strncmp(cmd_args[0], "export", 6))
		builtin_export(mini, cmd_args);
	if (ft_strlen(cmd_args[0]) == 5 && !ft_strncmp(cmd_args[0], "unset", 5))
		builtin_unset(mini, cmd_args);
	if (ft_strlen(cmd_args[0]) == 3 && !ft_strncmp(cmd_args[0], "env", 3))
		builtin_env(mini, cmd_args);
	if (ft_strlen(cmd_args[0]) == 4 && !ft_strncmp(cmd_args[0], "exit", 4))
		builtin_exit(mini, cmd_args, i);
}
