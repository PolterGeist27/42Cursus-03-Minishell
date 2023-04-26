/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:46:22 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/26 16:40:25 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *limiter, t_minishell *mini)
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
/* 	mini->in_fd = open(".heredoc", O_RDONLY);
	if (!mini->in_fd)
	{
		perror(strerror(errno));
		exit(1);
	} */
}
