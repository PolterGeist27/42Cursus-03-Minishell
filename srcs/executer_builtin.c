/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:20:07 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/02 08:11:36 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *name)
{
	if (ft_strncmp(name, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(name, "cd", ft_strlen("cd")) == 0)
		return (2);
	if (ft_strncmp(name, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(name, "export", ft_strlen("export")) == 0)
		return (3);
	if (ft_strncmp(name, "unset", ft_strlen("unset")) == 0)
		return (4);
	if (ft_strncmp(name, "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(name, "exit", ft_strlen("exit")) == 0)
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
	if (ft_strncmp(cmd_args[0], "echo", ft_strlen("echo")) == 0)
		builtin_echo(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "cd", ft_strlen("cd")) == 0)
		builtin_cd(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "pwd", ft_strlen("pwd")) == 0)
		builtin_pwd(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "export", ft_strlen("export")) == 0)
		builtin_export(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "unset", ft_strlen("unset")) == 0)
		builtin_unset(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "env", ft_strlen("env")) == 0)
		builtin_env(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "exit", ft_strlen("exit")) == 0)
		builtin_exit(mini, cmd_args, i);
}
