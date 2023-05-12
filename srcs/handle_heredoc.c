/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:50:57 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 10:41:59 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc(t_minishell *mini, char **cmd_args, char *limiter)
{
	int			tempfile;
	char		*buff;

	tempfile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC,
			S_IWUSR | S_IRUSR);
	if (tempfile < 0)
	{
		ft_putstr_fd("minishell: Error creating .heredoc\n", 2);
		free_child(mini, cmd_args, 1);
	}
	while (1)
	{
		buff = readline(">");
		if (!buff)
		{
			ft_putstr_fd("minishell: warning: here-document", 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(limiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (!ft_strncmp(limiter, buff, ft_strlen(limiter) + 1))
			break ;
		if (ft_strrchr(buff, '$'))
			buff = expander(buff, mini);
		ft_putendl_fd(buff, tempfile);
		free(buff);
	}
	free(buff);
	close(tempfile);
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
