/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:32:31 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 10:43:33 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_files(char **args, t_minishell *mini)
{
	struct stat	statbuf;

	if (ft_strrchr(args[0], '/') || !mini->paths)
	{
		if (stat(args[0], &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				is_a_directory(args, mini);
			else if (!(statbuf.st_mode & S_IXUSR))
				permission_error(args, mini);
			return (1);
		}
		else
			return (0);
	}
	return (1);
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
			free_child(mini, 0, 0);
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
