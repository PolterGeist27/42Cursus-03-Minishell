/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:17:38 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 13:01:46 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		free(command);
		i++;
	}
	//free(command);
	return (0);
}

void	execute_cmd(t_minishell *mini, t_list *env, char *input, int i)
{
	int		pid;
	char	**cmd_args;
	char	*command;
	int		j;

	j = -1;
	(void)env;
	pid = fork();
	if (pid == 0)
	{
		redirections(mini, i);
		cmd_args = handle_redirs(mini, input);
		free(input);
		redirect(mini->in_fd, mini->out_fd);
		while (cmd_args[++j])
			if (ft_strrchr(cmd_args[j], '$'))
				cmd_args[i] = expander(cmd_args[j], &env);
		/* if (is_builtin(cmd_args[0]))
			execute_builtin(mini, env, cmd_args[0]); */
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0]);
		execve(command, cmd_args, 0);
	}
}

void	execute_multi_cmds(t_minishell *mini, t_list *env)
{
	int		i;
	char	*cmd;

	(void)env;
	i = 0;
	mini->pipe_fd = (int *)malloc(sizeof(int) * mini->pipe_num * 2);
	if (!mini->pipe_fd)
	{
		ft_putstr_fd("Memory allocation failed at mini->pipe_fd", 2);
		//clean function;
		exit(1);
	}
	open_pipes(mini);
	while (mini->args[i])
	{
		cmd = add_whitespaces(mini->args[i]);
		execute_cmd(mini, env, cmd, i);
		free(cmd);
		i++;
	}
	close_pipes(mini);
	free(mini->pipe_fd);
}

void	execute_single_cmd(t_minishell *mini, t_list *env, char *input)
{
	int		pid;
	char	**cmd_args;
	char	*command;
	int		i;

	(void)env;
	i = -1;
	pid = fork();
	if (pid == 0)
	{
		cmd_args = handle_redirs(mini, input);
		dup2(mini->in_fd, STDIN_FILENO);
		dup2(mini->out_fd, STDOUT_FILENO);
		while (cmd_args[++i])
			if (ft_strrchr(cmd_args[i], '$'))
				cmd_args[i] = expander(cmd_args[i], &env);
		/* if (is_builtin(cmd_args[0]))
			execute_builtin(mini, env, cmd_args[0]); */
		command = get_command(cmd_args[0], mini);
		if (!command)
			command_error(cmd_args[0]);
		execve(command, cmd_args, 0);
	}
}

void	executer(t_minishell *mini, t_list *env)
{
	char	*cmd;

	cmd = 0;
	if (mini->pipe_num > 0)
		execute_multi_cmds(mini, env);
	else
	{
		cmd = add_whitespaces(mini->args[0]);
		execute_single_cmd(mini, env, cmd);
		free(cmd);
	}
}
