/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 10:24:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/26 17:07:17 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*expand_and_rmquotes(char *arg)
{
	char	*temp;
	int		i;

	i = 0;
	
	return (temp);
} */

/* char	*get_command(char *arg, t_minishell *mini)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	while (mini->paths[i])
	{
		temp = ft_strdup(mini->paths[i]);
		command = ft_strjoin(temp, "/");
		free(temp);
		temp = ft_strdup(command);
		free(command);
		command = ft_strjoin(temp, arg);
		free(temp);
		if (access(command, F_OK) == 0)
			return (command);
		i++;
	}
	return (arg);
} */

/* t_command	*get_arguments(char *input, t_minishell *mini)
{
	t_command	*cmd;
    char        *spaced;
	//int			i;
	
	//i = -1;
	cmd = (t_command *)malloc(sizeof(t_command));
    spaced = add_whitespaces(input);
    free(input);
    cmd->args = split_meta(spaced, ' ');
	cmd->command = get_command(cmd->args[0], mini);
	if (!cmd->command)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		//exit_status (2);
	}
	cmd->in_fd = 0;
	cmd->out_fd = 1;
    while (cmd->args[++i])
		cmd->args[i] = expand_and_rmquotes(cmd->args[i]);
	return (cmd);
}

t_list    *cmd_list(t_minishell *mini, char *input, t_list *env)
{
	int	i;
	t_list	*head;
	t_list	*temp;

	i = 0;
	head = 0;
	mini->cmd_num = ft_wordcount_meta(input, '|');
	mini->pipe_num = mini->cmd_num - 1;
	mini->args = split_meta(input, '|');
	mini->paths = ft_split(get_info_env(&env, "PATH"), ':');
	ft_lstadd_back(&head, ft_lstnew(get_arguments(mini->args[i++], mini)));
	temp = head;
	while (mini->args[i])
	{
		temp->next = ft_lstnew(get_arguments(mini->args[i], mini));
		temp = temp->next;
		i++;
	}
    ft_free_split(mini->args);
	return (head);
} */

void	input_handler(t_minishell *mini, char *input, t_list *env)
{
	mini->cmd_num = ft_wordcount_meta(input, '|');
	mini->pipe_num = mini->cmd_num - 1;
	mini->args = split_meta(input, '|');
	mini->paths = ft_split(get_info_env(&env, "PATH"), ':');
	mini->in_fd = 0;
	mini->out_fd = 1;
}
