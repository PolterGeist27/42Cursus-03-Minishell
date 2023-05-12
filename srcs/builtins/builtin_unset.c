/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:16:33 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 12:04:41 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	remove_from_exp(t_minishell *mini, char *name)
{
	t_list	*tp;
	t_list	*previous;

	tp = mini->export;
	previous = 0;
	while (tp)
	{
		if ((ft_strlen(((t_exp *)tp->content)->name) == ft_strlen(name))
			&& !ft_strncmp(((t_exp *)tp->content)->name, name, ft_strlen(name)))
		{
			if (previous != 0)
				previous->next = tp->next;
			else
				mini->env = tp->next;
			free(((t_exp *)tp->content)->name);
			free(((t_exp *)tp->content)->info);
			free(((t_exp *)tp->content));
			free(tp);
			return ;
		}
		previous = tp;
		tp = tp->next;
	}
}

static	void	remove_from_env(t_minishell *mini, char *name)
{
	t_list	*tp;
	t_list	*previous;

	tp = mini->env;
	previous = 0;
	while (tp)
	{
		if ((ft_strlen(((t_env *)tp->content)->name) == ft_strlen(name))
			&& !ft_strncmp(((t_env *)tp->content)->name, name, ft_strlen(name)))
		{
			if (previous != 0)
				previous->next = tp->next;
			else
				mini->env = tp->next;
			free(((t_env *)tp->content)->name);
			free(((t_env *)tp->content)->info);
			free(((t_env *)tp->content));
			free(tp);
			return ;
		}
		previous = tp;
		tp = tp->next;
	}
}

static void	unset_error(t_minishell *mini, char **cmd_args)
{
	ft_putstr_fd("minishell: unset: no options supported\n", 2);
	free_child(mini, cmd_args, 0);
	g_exit_status = 2;
	exit (2);
}

void	check_unset(t_minishell *mini, char **cmd_args)
{
	int		status;
	int		i;

	i = 0;
	while (cmd_args[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status == 0)
	{
		if (i > 1)
		{
			i = 1;
			while (cmd_args[i])
			{
				remove_from_env(mini, cmd_args[i]);
				remove_from_exp(mini, cmd_args[i]);
				i++;
			}
		}
	}
}

void	builtin_unset(t_minishell *mini, char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	if (i == 1)
	{
		free_child(mini, cmd_args, 1);
		g_exit_status = 0;
		exit (0);
	}
	else if (i > 1)
	{
		if (cmd_args[1][0] == '-')
			unset_error(mini, cmd_args);
		i = 0;
		while (cmd_args[i])
		{
			free_child(mini, cmd_args, 0);
			g_exit_status = 0;
			exit (0);
		}
	}
}
