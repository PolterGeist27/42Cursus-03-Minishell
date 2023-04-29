/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:38:26 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/29 12:17:12 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_error(char *command, char **cmd_args, t_minishell *mini)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 127;
	exit(127);
}

void	file_error(char **cmd_args, t_minishell *mini)
{
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 127;
	exit(127);
}