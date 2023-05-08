/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:30:23 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/08 14:02:59 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

int	isalnumextra(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
		return (1);
	else
		return (0);
}

void	get_exit_status(void)
{
	pid_t	i;
	int		status;

	i = 1;
	status = 0;
	while (i > 0)
	{
		signal(SIGINT, &handler_sigint);
		i = waitpid(0, &status, 0);
		if (i < 0)
			break ;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	free_child(t_minishell *mini, char **cmd_args, int i)
{
	if (cmd_args)
		ft_free_split(cmd_args);
	if (mini->pipe_fd)
		free(mini->pipe_fd);
	unlink(".heredoc");
	if (mini->paths)
		ft_free_split(mini->paths);
	if (mini->cmd_args)
		ft_free_split(mini->cmd_args);
	if (mini->args)
		ft_free_split(mini->args);
	free_env(mini->env);
	if (i == 1)
	{
		g_exit_status = 1;
		exit(1);
	}
}

void	free_main(t_minishell *mini, int i)
{
	if (mini->pipe_fd)
		free(mini->pipe_fd);
	unlink(".heredoc");
	if (mini->paths)
		ft_free_split(mini->paths);
	if (mini->args)
		ft_free_split(mini->args);
	if (i == 1)
		free_env(mini->env);
}
