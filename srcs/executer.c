/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:17:38 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/03 11:55:37 by pealexan         ###   ########.fr       */
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

void	execute_cmd(t_minishell *mini, char *cmd, int i)
{
	int		pid;
	char	*command;
	char	**cmd_args;

	if (mini->heredoc)
		wait(0);
	pid = fork();
	if (pid == 0)
	{
		signal_default();
		cmd_args = handle_redirs(mini, cmd);
		redirections(mini, i);
		redirect(mini->in_fd, mini->out_fd);
		expand_args(cmd_args, mini);
		if (!cmd_args[0])
			free_child(mini, cmd_args, 1);
		if (is_builtin(cmd_args[0]))
			execute_builtin(mini, cmd_args, 0);
		if (!check_files(cmd_args, mini))
			file_error(cmd_args, mini);
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0], cmd_args, mini);
		execve(command, cmd_args, convert_env(mini));
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
		check_heredoc(mini, i);
		execute_cmd(mini, cmd, i);
		free(cmd);
		i++;
	}
	close_pipes(mini);
}

void	execute_single_cmd(t_minishell *mini, char *cmd)
{
	int		pid;
	char	*command;
	char	**cmd_args;

	pid = fork();
	if (pid == 0)
	{
		signal_default();
		cmd_args = handle_redirs(mini, cmd);
		redirect(mini->in_fd, mini->out_fd);
		expand_args(cmd_args, mini);
		if (!cmd_args[0])
			free_child(mini, cmd_args, 1);
		if (is_builtin(cmd_args[0]))
			execute_builtin(mini, cmd_args, 1);
		if (!check_files(cmd_args, mini))
			file_error(cmd_args, mini);
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0], cmd_args, mini);
		execve(command, cmd_args, convert_env(mini));
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
		mini->cmd_args = remove_redirs(cmd);
		execute_single_cmd(mini, cmd);
		free(cmd);
		check_builtin(mini, mini->cmd_args);
		ft_free_split(mini->cmd_args);
	}
	get_exit_status();
}
