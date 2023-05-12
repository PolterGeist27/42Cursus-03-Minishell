/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:50:57 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 10:55:30 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	end_of_file_error(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}

static void	heredoc_file_error(t_minishell *mini, char **cmd_args)
{
	ft_putstr_fd("minishell: Error creating .heredoc\n", 2);
	free_child(mini, cmd_args, 1);
}

static void	heredoc(t_minishell *mini, char **cmd_args, char *limiter)
{
	int			tempf;
	char		*buff;

	tempf = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (tempf < 0)
		heredoc_file_error(mini, cmd_args);
	while (1)
	{
		buff = readline(">");
		if (!buff)
		{
			end_of_file_error(limiter);
			break ;
		}
		if (!ft_strncmp(limiter, buff, ft_strlen(limiter) + 1))
			break ;
		if (ft_strrchr(buff, '$'))
			buff = expander(buff, mini);
		ft_putendl_fd(buff, tempf);
		free(buff);
	}
	free(buff);
	close(tempf);
}

void	handle_heredoc(char **cmd_args, t_minishell *mini, int *i, int *count)
{
	heredoc(mini, cmd_args, cmd_args[*i + 1]);
	mini->in_fd = open(".heredoc", O_RDONLY);
	if (mini->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(".heredoc", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_child(mini, cmd_args, 1);
		exit(1);
	}
	shift_redir(cmd_args, i, count);
}
