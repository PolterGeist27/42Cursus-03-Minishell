/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:40:07 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 12:50:36 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shift_redir(char **cmd_args, int *i, int *count)
{
	int	index;

	index = *i;
	while (index < *count - 2)
	{
		free(cmd_args[index]);
		cmd_args[index] = ft_strdup(cmd_args[index + 2]);
		index++;
	}
	*count = *count - 2;
	cmd_args[index] = 0;
	*i = -1;
}

static void	handle_app(char **cmd_args, t_minishell *mini, int *i, int *count)
{
	char	*file;

	if (ft_strrchr(cmd_args[*i + 1], '$'))
	{
		file = expander(cmd_args[*i + 1], &mini->env);
		mini->out_fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		free(file);
	}
	else
		mini->out_fd = open(cmd_args[*i + 1], O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	if (mini->out_fd < 0)
	{
		ft_putstr_fd("Error creating file\n", 2);
		//clean_function;
		exit(1);
	}
	shift_redir(cmd_args, i, count);
}

static void	handle_out(char **cmd_args, t_minishell *mini, int *i, int *count)
{
	char	*file;

	if (ft_strrchr(cmd_args[*i + 1], '$'))
	{
		file = expander(cmd_args[*i + 1], &mini->env);
		mini->out_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		free(file);
	}
	else
		mini->out_fd = open(cmd_args[*i + 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (mini->out_fd < 0)
	{
		ft_putstr_fd("Error creating file\n", 2);
		//clean_function;
		exit(1);
	}
	shift_redir(cmd_args, i, count);
}

static void	handle_in(char **cmd_args, t_minishell *mini, int *i, int *count)
{
	char	*file;

	if (ft_strrchr(cmd_args[*i + 1], '$'))
	{
		file = expander(cmd_args[*i + 1], &mini->env);
		mini->in_fd = open(file, O_RDONLY);
		free(file);
	}
	else
		mini->in_fd = open(cmd_args[*i + 1], O_RDONLY);
	if (mini->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_args[*i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//clean_function;
		exit(1);
	}
	shift_redir(cmd_args, i, count);
}

char	**handle_redirs(t_minishell *mini, char *input)
{
	char	**cmd_args;
	int		i;
	int		count;

	i = 0;
	count = ft_wordcount_meta(input, ' ');
	cmd_args = split_meta(input, ' ');
	while (cmd_args[i])
	{
		if (ft_strncmp(cmd_args[i], "<", ft_strlen(cmd_args[i])) == 0)
			handle_in(cmd_args, mini, &i, &count);
		else if (ft_strncmp(cmd_args[i], ">", ft_strlen(cmd_args[i])) == 0)
			handle_out(cmd_args, mini, &i, &count);
		else if (ft_strncmp(cmd_args[i], ">>", ft_strlen(cmd_args[i])) == 0)
			handle_app(cmd_args, mini, &i, &count);
		else if (ft_strncmp(cmd_args[i], "<<", ft_strlen(cmd_args[i])) == 0)
			handle_heredoc(cmd_args, mini, &i, &count);
		i++;
	}
	return (cmd_args);
}
