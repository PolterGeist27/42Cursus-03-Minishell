/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:21:35 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 12:36:16 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit(t_minishell *mini, char **cmd_args)
{
	int		status;

	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status != 1)
	{
		ft_free_split(cmd_args);
		free_main(mini, 1);
		exit (g_exit_status);
	}
}

static void	exit_error3(t_minishell *mini, char **cmd_args)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_exit_status = 2;
	free_child(mini, cmd_args, 0);
	exit (g_exit_status);
}

static void	exit_error1(t_minishell *mini, char **cmd_args, int i)
{
	if (i == 2)
	{
		g_exit_status = (ft_atoi(cmd_args[1]) % 256);
		free_child(mini, cmd_args, 0);
		exit (g_exit_status);
	}
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		free_child(mini, cmd_args, 0);
		exit (1);
	}
}

void	builtin_exit(t_minishell *mini, char **cmd_args, int x)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	if (x == 1)
		ft_putstr_fd("exit\n", 2);
	if (i > 1)
	{
		if (ft_isnumeric(cmd_args[1]))
			exit_error1(mini, cmd_args, i);
		else
			exit_error3(mini, cmd_args);
	}
	else
	{
		free_child(mini, cmd_args, 0);
		g_exit_status = 0;
		exit(g_exit_status);
	}
}
