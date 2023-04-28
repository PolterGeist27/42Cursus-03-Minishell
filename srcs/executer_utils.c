/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:32:31 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 13:01:41 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_error(char *command)
{
	ft_putstr_fd(command, 2);
	//free(command);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	open_pipes(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_num - 1)
	{
		if (pipe(mini->pipe_fd + (2 * i)) < 0)
		{
			ft_putstr_fd("Pipe creation failed\n", 2);
			//clean_function
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_num * 2)
	{
		close(mini->pipe_fd[i]);
		i++;
	}
}

void	redirections(t_minishell *mini, int i)
{
	if (i == 0)
		redirect(mini->in_fd, mini->pipe_fd[1]);
	else if (i == mini->cmd_num - 1)
		redirect(mini->pipe_fd[2 * i - 2], mini->out_fd);
	else
		redirect(mini->pipe_fd[2 * i - 2], mini->pipe_fd[2 * i + 1]);
	close_pipes(mini);
}

void	redirect(int a, int b)
{
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
}
