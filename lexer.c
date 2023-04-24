/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:11:33 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/18 09:45:21 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

        ls >a a | cat a > '123 ab$c' | echo "abc|deff $USER"

char	*trim_words(char *input, t_command *cmd)
{
	int	i;
	char	*words;

	cmd->redir = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strrchr(" \t\n", input[i]))
			i++;
		if (input[i] && ft_strrchr("><", input[i]))
			handle_redirs(input + i, cmd);	
		if (input[i] && ft_strrchr("\"\'", input[i]))
			words = handle_quotes(input + i, &i);
		else
			words = handle_words(input + i, &i);
		while (input[i] && ft_strrchr(" \t\n", input[i]))
			i++;
	}
	return (words);
}

t_redir	*get_redirs(char *input, int type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (input[i] == '>' && input[i + 1] && input[i + 1] != '>')
		redir->type = 1;
	else if (input[i] == '<' && input[i + 1] && input[i + 1] != '<')
		redir->type = 2;
	else if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
	{
		redir->type = 3;
		i++;
	}
	else if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
	{
		redir->type = 4;
		i++;
	}
	redir->file = 
	return (redir);
}

t_list	*handle_redirs(char *input)
{
	int		i;
	t_list	*head;
	t_list	*temp;
	
	i = 0;
	head = 0;
	ft_lstadd_back(&cmd->redir, ft_lstnew(get_redirs(input)));
	temp = head;
	while (input[i])
	{
		if (input[i] && ft_strrchr("><", input[i]))
		{
			temp->next = ft_lstnew(get_redirs(input));
			temp = temp->next;
		}
		i++;
	}
	return (head);
}

t_command	*get_commands(char *input, int *i)
{
	t_command	*cmd;
	int			j;
	
	j = 0;
	head = 0;
	cmd = (t_command *)malloc(sizeof(t_command));
	while (input[i])
	{
		if (input[i] && ft_strrchr("><", input[i]))
			cmd->redir = handle_redirs(input);
		i++;
	}
	cmd->words = trim_words(words, cmd);
	return (cmd);
}


t_list    *lexer(char *input)
{
	int	i;
	char	**cmds;
	t_list	*head;
	t_list	*temp;

	i = 0;
	head = 0;
	ft_lstadd_back(&head, ft_lstnew(get_commands(cmds[i], &i)));
	temp = head;
	while (input[i])
	{
		if (input[i] == ft_strrchr("|", input[i]))
		{
			temp->next = ft_lstnew(get_commands(cmds[i]))
			temp = temp->next;
		}
		i++;
	}
	return (head);	
}