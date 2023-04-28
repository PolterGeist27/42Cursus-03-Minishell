/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:24:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 09:56:44 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input_handler(t_minishell *mini, char *input, t_list *env)
{
	mini->cmd_num = ft_wordcount_meta(input, '|');
	mini->pipe_num = mini->cmd_num - 1;
	mini->args = split_meta(input, '|');
	free(input);
	mini->paths = ft_split(get_info_env(&env, "PATH"), ':');
	mini->in_fd = STDIN_FILENO;
	mini->out_fd = STDOUT_FILENO;
	mini->pipe_fd = 0;
	mini->pid = 0;
}

int	read_input(t_minishell *mini, t_list *env)
{
	char		*input;
	
	input = readline(":> ");
	if (ft_strlen(input) > 0)
		add_history(input);
	if (!valid_input(input))
	{
		free(input);
		return (0);
	}
	input_handler(mini, input, env);
	return (1);
}
