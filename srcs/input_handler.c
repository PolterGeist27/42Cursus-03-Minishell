/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:24:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/30 17:13:25 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	input_handler(t_minishell *mini, char *input)
{
	char	*temp;
	char	**temp_args;
	int		i;

	i = -1;
	mini->heredoc = 0;
	temp = add_whitespaces(input);
	temp_args = split_meta(temp, ' ');
	while (temp_args[++i])
		if (ft_strncmp(temp_args[i], "<<", ft_strlen(temp_args[i])) == 0)
			mini->heredoc = 1;
	mini->cmd_num = ft_wordcount_meta(input, '|');
	mini->pipe_num = mini->cmd_num - 1;
	mini->args = split_meta(input, '|');
	mini->paths = ft_split(get_info_env(&mini->env, "PATH"), ':');
	mini->in_fd = STDIN_FILENO;
	mini->out_fd = STDOUT_FILENO;
	mini->pipe_fd = 0;
	mini->pid = 0;
	free(temp);
	ft_free_split(temp_args);
}

static char	*get_prompt(void)
{
	char	*temp;
	char	*prompt;

	prompt = getenv("USER");
	temp = ft_strdup(prompt);
	prompt = ft_strjoin(temp, "@42porto > ");
	free(temp);
	return (prompt);
}

int	read_input(t_minishell *mini)
{
	char		*input;
	char		*prompt;
	char		*trimmed;

	prompt = get_prompt();
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (0);
	if (ft_strlen(input) > 0)
		add_history(input);
	trimmed = ft_strtrim(input, " ");
	free(input);
	if (!valid_input(trimmed))
	{
		free(trimmed);
		g_exit_status = 2;
		return (0);
	}
	input_handler(mini, trimmed);
	free(trimmed);
	return (1);
}
