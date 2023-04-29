/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:17:38 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/29 14:02:04 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command(char *arg, t_minishell *mini)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	if (access(arg, X_OK) == 0)
		return (arg);
	while (mini->paths[i])
	{
		temp = ft_strdup(mini->paths[i]);
		command = ft_strjoin(temp, "/");
		free(temp);
		temp = ft_strdup(command);
		free(command);
		command = ft_strjoin(temp, arg);
		if (access(command, F_OK) == 0)
			return (command);
		free(temp);
		free(command);
		i++;
	}
	return (0);
}

void	execute_cmd(t_minishell *mini, char *input, int i)
{
	int		pid;
	char	**cmd_args;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		cmd_args = handle_redirs(mini, input);
		free(input);
		redirections(mini, i);
		redirect(mini->in_fd, mini->out_fd);
		expand_args(cmd_args, mini);
		if (!cmd_args[0])
			free_child(mini, cmd_args, 1);
		if (ft_strrchr(cmd_args[0], '/'))
			if (!check_files(cmd_args, mini))
				file_error(cmd_args, mini);
		/* if (is_builtin(cmd_args[0]))
			execute_builtin(mini, env, cmd_args[0]); */
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0], cmd_args, mini);
		execve(command, cmd_args, 0);
	}
}

void	execute_multi_cmds(t_minishell *mini)
{
	int		i;
	char	*cmd;

	i = 0;
	mini->pipe_fd = (int *)malloc(sizeof(int) * mini->pipe_num * 2);
	if (!mini->pipe_fd)
	{
		ft_putstr_fd("Memory allocation failed at mini->pipe_fd", 2);
		free_child(mini, 0, 1);
	}
	open_pipes(mini);
	while (mini->args[i])
	{
		cmd = add_whitespaces(mini->args[i]);
		execute_cmd(mini, cmd, i);
		free(cmd);
		i++;
	}
	//free(cmd);
	close_pipes(mini);
}

void	execute_single_cmd(t_minishell *mini, char *input)
{
	int		pid;
	char	**cmd_args;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		cmd_args = handle_redirs(mini, input);
		free(input);
		redirect(mini->in_fd, mini->out_fd);
		expand_args(cmd_args, mini);
		if (!cmd_args[0])
			free_child(mini, cmd_args, 1);
		if (ft_strrchr(cmd_args[0], '/'))
			if (!check_files(cmd_args, mini))
				file_error(cmd_args, mini);
		/* if (is_builtin(cmd_args[0]))
			execute_builtin(mini, env, cmd_args[0]); */
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0], cmd_args, mini);
		execve(command, cmd_args, 0);
	}
}

void	executer(t_minishell *mini)
{
	char	*cmd;

	cmd = 0;
	if (mini->pipe_num > 0)
		execute_multi_cmds(mini);
	else
	{
		cmd = add_whitespaces(mini->args[0]);
		execute_single_cmd(mini, cmd);
		free(cmd);
	}
}
