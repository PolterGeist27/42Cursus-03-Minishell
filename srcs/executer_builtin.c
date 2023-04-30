/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:20:07 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/30 15:30:23 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_minishell *mini, char **cmd_args)
{
	size_t	len;

	len = ft_strlen(cmd_args[0]);
/* 	if (ft_strncmp(cmd_args[0], "echo", len) == 0)
		builtin_echo(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "cd", len) == 0)
		builtin_cd(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "pwd", len) == 0)
		builtin_pwd(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "export", len) == 0)
		builtin_export(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "unset", len) == 0)
		builtin_unset(mini, cmd_args); */
	if (ft_strncmp(cmd_args[0], "env", len) == 0)
		builtin_env(mini, cmd_args);
	if (ft_strncmp(cmd_args[0], "exit", len) == 0)
		builtin_exit(mini, cmd_args, 0);
	return (0);
}
