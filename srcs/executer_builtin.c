/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:20:07 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/30 19:22:37 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (ft_strncmp(name, "echo", len) == 0)
		return (1);
	if (ft_strncmp(name, "cd", len) == 0)
		return (2);
	if (ft_strncmp(name, "pwd", len) == 0)
		return (1);
	if (ft_strncmp(name, "export", len) == 0)
		return (3);
	if (ft_strncmp(name, "unset", len) == 0)
		return (4);
	if (ft_strncmp(name, "env", len) == 0)
		return (1);
	if (ft_strncmp(name, "exit", len) == 0)
		return (5);
	return (0);
}

void	check_builtin(t_minishell *mini, char **cmd_args)
{
	expand_args(cmd_args, mini);
	if (is_builtin(cmd_args[0]) == 2)
		check_cd(mini, cmd_args);
	/* else if (is_builtin(cmd_args[0]) == 3)
		check_export(mini, cmd_args);
	else if (is_builtin(cmd_args[0]) == 4)
		check_unset(mini, cmd_args[0]); */
	else if (is_builtin(cmd_args[0]) == 5)
		check_exit(mini, cmd_args);
}

void	execute_builtin(t_minishell *mini, char **cmd_args, int i)
{
	size_t	len;

	len = ft_strlen(cmd_args[0]);
//	if (ft_strncmp(cmd_args[0], "echo", len) == 0)
//		builtin_echo(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "cd", len) == 0)
		builtin_cd(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "pwd", len) == 0)
		builtin_pwd(mini, cmd_args);
//	if (ft_strncmp(cmd_args[0], "export", len) == 0)
//		builtin_export(mini, cmd_args);
//	if (ft_strncmp(cmd_args[0], "unset", len) == 0)
//		builtin_unset(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "env", len) == 0)
		builtin_env(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "exit", len) == 0)
		builtin_exit(mini, cmd_args, i);
}
