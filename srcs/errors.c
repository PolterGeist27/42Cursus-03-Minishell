/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:38:26 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 10:06:45 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_error2(t_minishell *mini, char **cmd_args)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd(": Invalid option\n", 2);
	free_child(mini, cmd_args, 0);
	exit (2);
}

void	command_error(char *command, char **cmd_args, t_minishell *mini)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 127;
	exit(127);
}

void	permission_error(char **cmd_args, t_minishell *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 126;
	exit(126);
}

void	file_error(char **cmd_args, t_minishell *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 127;
	exit(127);
}

void	is_a_directory(char **cmd_args, t_minishell *mini)
{
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 126;
	exit(126);
}
