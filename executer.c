/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:17:38 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/26 17:03:02 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *arg, t_minishell *mini)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	while (mini->paths[i])
	{
		temp = ft_strdup(mini->paths[i]);
		command = ft_strjoin(temp, "/");
		free(temp);
		temp = ft_strdup(command);
		free(command);
		command = ft_strjoin(temp, arg);
		free(temp);
		if (access(command, F_OK) == 0)
			return (command);
		i++;
	}
	return (0);
}

void	execute_cmd(t_minishell *mini, t_list *env, char *input, int i)
{
	int		pid;
	char	**cmd_args;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
			redirect(mini->in_fd, mini->pipe_fd[1]);
		else if (i == mini->cmd_num - 1)
			redirect(mini->pipe_fd[2 * i - 2], mini->out_fd);
		else
			redirect(mini->pipe_fd[2 * i - 2], mini->pipe_fd[2 * i + 1]);
		close_pipes(mini);
		cmd_args = handle_redirs(mini, input);
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0]);
		dup2(mini->in_fd, STDIN_FILENO);
		dup2(mini->out_fd, STDOUT_FILENO);
		execve(command, cmd_args, 0);
	}
}

void	execute_multi_cmds(t_minishell *mini, t_list *env)
{
	int	i;

	i = 0;
	mini->pipe_fd = (int *)malloc(sizeof(int) * mini->pipe_num * 2);
	if (!mini->pipe_fd)
	{
		ft_putstr_fd("Memory allocation failed at mini->pipe_fd", 2);
		//clean function;
		exit(1);
	}
	open_pipes(mini);
	while (i < mini->cmd_num)
	{
		execute_cmd(mini, env, add_whitespaces(mini->args[i]), i);
		i++;
	}
	close_pipes(mini);
}

void	execute_single_cmd(t_minishell *mini, t_list *env, char *input)
{
	int		pid;
	char	**cmd_args;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		cmd_args = handle_redirs(mini, input);
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0]);
		dup2(mini->in_fd, STDIN_FILENO);
		dup2(mini->out_fd, STDOUT_FILENO);
		execve(command, cmd_args, 0);
	}
}
