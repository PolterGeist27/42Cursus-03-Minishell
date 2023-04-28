/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:50:57 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 09:53:42 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc(char *limiter)
{
	int		tempfile;
	char	*buff;

	tempfile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (tempfile < 0)
	{
		perror(strerror(errno));
		exit (1);
	}
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		buff[ft_strlen(buff) - 1] = '\0';
		if (!buff)
			exit(errno);
		if (!ft_strncmp(limiter, buff, ft_strlen(limiter) + 1))
			break ;
		write(tempfile, buff, ft_strlen(buff));
		write(tempfile, "\n", 1);
		free(buff);
	}
	free(buff);
	close(tempfile);
}

void	handle_heredoc(char **cmd_args, t_minishell *mini, int *i, int *count)
{
	heredoc(cmd_args[*i + 1]);
	mini->in_fd = open(".heredoc", O_RDONLY);
	if (mini->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(".heredoc", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//clean_function;
		exit(1);
	}
	shift_redir(cmd_args, i, count);
}