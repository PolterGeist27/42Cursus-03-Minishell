/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:46:22 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/12 15:38:29 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != (unsigned char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_wordlen(const char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	return (i);
}

char	**ft_strtok(const char *s, char *set)
{
	char	**words;
	int		wdcount;
	int		j;

	j = 0;
	if (!s)
		return (0);
	wdcount = ft_wordcount(s, set);
	words = malloc(sizeof(char *) * (wdcount + 1));
	if (!words)
		return (0);
	while (*s)
	{
		while (*s && ft_strchr(set, *s))
			s++;
		if (*s)
			words[j++] = ft_substr(s, 0, ft_wordlen(s, c));
		while (*s && !ft_strchr(set, *s))
			s++;
	}
	words[j] = 0;
	return (words);
} */

void	init_mini(t_minishell *mini, char **env)
{
	while (ft_strncmp(*env, "PATH", 4))
		env++;
	mini->paths = ft_split(*env + 5, ':');
	mini->in_fd = 0;
	mini->out_fd = 1;
	mini->cmd_num = 0;
	mini->pipe_num = 0;
}

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
		write(1, "heredoc> ", 9);
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
	mini->in_fd = open(".heredoc", O_RDONLY);
	if (!mini->in_fd)
	{
		perror(strerror(errno));
		exit(1);
	}
}

void	parse_line(t_minishell *mini, char *buffer)
{
	int	i;
	char	**args;

	i = 0;
	args = ft_split(buffer, ' ');
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", ft_strlen(args[i]))  == 0)
			mini->pipe_num++;
		if (ft_strncmp(args[i], "<", ft_strlen(args[i]))  == 0)
		{
			mini->in_fd = open(args[i + 1], O_RDONLY);
			if (!mini->in_fd)
			{
				perror(strerror(errno));
				exit(1);
			}
		}
		if (ft_strncmp(args[i], ">", ft_strlen(args[i]))  == 0)
			mini->out_fd = open(args[i + 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (ft_strncmp(args[i], ">>", ft_strlen(args[i]))  == 0)
			mini->out_fd = open(args[i + 1], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (ft_strncmp(args[i], "<<", ft_strlen(args[i]))  == 0)
			heredoc(args[i + 1], mini);
		i++;
	} 
}

int	main(int ac, char **av, char **env)
{
	t_env		envinfo;
	t_minishell	mini;
	char		*buffer;

	init_mini(&mini, env);
	get_envvariables(&envinfo);
	while (1)
	{
		get_prompt(&envinfo, &mini);
		buffer = readline(mini.prompt);
		add_history(buffer);
		parse_line(&mini, buffer);
		free(mini.prompt);
		free(buffer);
	}
	return (0);
}
