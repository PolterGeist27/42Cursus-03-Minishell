/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 08:46:22 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/13 17:21:33 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_minishell *mini, char **env)
{
	while (ft_strncmp(*env, "PATH", 4))
		env++;
	mini->paths = ft_split(*env + 5, ':');
	mini->in_fd = 0;
	mini->out_fd = 1;
	mini->cmd_num = 1;
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
	mini->in_fd = open(".heredoc", O_RDONLY);
	if (!mini->in_fd)
	{
		perror(strerror(errno));
		exit(1);
	}
}

void	count_pipes(t_minishell *mini, char *buffer)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(buffer, ' ');
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", ft_strlen(args[i]))  == 0)
			mini->pipe_num++;
	}
	ft_free_split(args);
}

void	split_line(t_minishell *mini, char *buffer)
{
	int	i;

	i = 0;
	mini->cmd_num = ft_wordcount(buffer, '|');
	count_pipes(mini, buffer);
	mini->args = ft_split(buffer, '|');
}


/* void	open_pipes(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_num - 1)
	{
		if (pipe(mini->pipe_fd + (2 * i)) < 0)
			return ;
			//ft_freemain(pipex);
		i++;
	}
}

void	close_pipes(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_num * 2)
	{
		close(mini->pipe_fd[i]);
		i++;
	}
} */

/* void	processes(t_minishell *mini, char **env, char *input)
{
	int		pid;
	char	**args;
	char	*command;

	pid = fork();
	if (pid == 0)
	{
		parse_input(mini, input);
		if (p->ix == 0)
			ft_redirect(p->infile_fd, p->pipe_fd[1]);
		else if (p->ix == p->cmd_nb - 1)
			ft_redirect(p->pipe_fd[2 * p->ix - 2], p->outfile_fd);
		else
			ft_redirect(p->pipe_fd[2 * p->ix - 2], p->pipe_fd[2 * p->ix + 1]);
		close_pipes(mini);
		args = ft_args(argv, p);
		command = ft_getcommand(args[0], p);
		if (!command)
		{
			perror(strerror(errno));
			ft_freechild(args, command);
			exit(errno);
		}
		execve(command, args, env);
	}
} */

/* void	execute_cmds(t_minishell *mini, char **env)
{
	int	i;

	i = 0;
	mini->pipe_fd = (int *)malloc(sizeof(int) * mini->pipe_num * 2);
	//if (!mini->pipe_fd)
	//	return (ft_errormsg(strerror(errno)));
	open_pipes(mini);
	while (i < mini->cmd_num)
		processes(mini, env, mini->args[i]);
	close_pipes(mini);
} */

char	**parse_input(t_minishell *mini, char *input)
{
	char	**cmd_args;
	int		i;
	int		count;
	int		index;

	i = 0;
	count = ft_wordcount(input, ' ');
	cmd_args = ft_split(input, ' ');
	while (cmd_args[i])
	{
		/* if (ft_strncmp(cmd_args[i], "<", ft_strlen(cmd_args[i]))  == 0)
		{
			if (!cmd_args[i + 1])
				exit(1);
			mini->in_fd = open(cmd_args[i + 1], O_RDONLY);
			if (!mini->in_fd)
			{
				perror(strerror(errno));
				exit(1);
			}
		} */
		if (ft_strncmp(cmd_args[i], ">", ft_strlen(cmd_args[i]))  == 0)
		{
			if (!cmd_args[i + 1])
			{
				printf("ERROR\n");
				exit(1);
			}
			mini->out_fd = open(cmd_args[i + 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			index = i;
			while (index < count - 2)
			{
				free(cmd_args[index]);
				cmd_args[index] = ft_strdup(cmd_args[index + 2]);
				index++;
			}
			count -= 2;
			cmd_args[index] = 0;
			i = -1;
		}
		/* if (ft_strncmp(cmd_args[i], ">>", ft_strlen(cmd_args[i]))  == 0)
		{
			if (!cmd_args[i + 1])
				exit(1);
			mini->out_fd = open(cmd_args[i + 1], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		}
		if (ft_strncmp(cmd_args[i], "<<", ft_strlen(cmd_args[i]))  == 0)
		{
			if (!cmd_args[i + 1])
				exit(1);
			heredoc(cmd_args[i + 1], mini);
		} */
		i++;
	}
	return (cmd_args);
}

char	*getcommand(char *arg, t_minishell *mini)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	if (arg[0] == '.')
		return (arg);
	while (mini->paths[i])
	{
		temp = ft_strjoin(mini->paths[i], "/");
		command = ft_strjoin(temp, arg);
		if (access(command, X_OK) == 0)
			return (command);
		i++;
	}
	return (0);
}

void	execute_single_cmd(t_minishell *mini, char *buffer)
{
	int		pid;
	char	**cmd_args;
	char	*command;
	int		i;
	
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		cmd_args = parse_input(mini, buffer);
		command = getcommand(cmd_args[0], mini);
		dup2(mini->in_fd, STDIN_FILENO);
		dup2(mini->out_fd, STDOUT_FILENO);
		if (!command)
		{
			printf("WHATUP?\n");
			exit(1);
		}
		execve(command, cmd_args, 0);
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
		//split_line(&mini, buffer);
		/* if (mini.pipe_num > 0)
			execute_cmds(&mini, buffer); */
		//else
		execute_single_cmd(&mini, buffer);
		wait(0);
		free(mini.prompt);
		free(buffer);
	}
	ft_free_split(mini.paths);
	return (0);
}
