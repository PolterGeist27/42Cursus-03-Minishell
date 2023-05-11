/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:29:35 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/11 13:03:25 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_export(char **env)
{
	int		i;
	t_list	*head;
	t_list	*tmp;

	i = 0;
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(ft_create_export(env[i])));
	tmp = head;
	i++;
	while (env[i] != NULL)
	{
		tmp->next = ft_lstnew(ft_create_export(env[i]));
		tmp = tmp->next;
		i++;
	}
	return (head);
}

t_exp	*ft_create_export(char *info)
{
	t_exp	*data;

	data = (t_exp *)malloc(sizeof(t_exp));
	data->name = get_name(info);
	data->info = add_declare(info);
	return (data);
}

int	modify_export(t_list *exp, char *name, char *changed_info)
{
	t_list	*tp;

	if (!exp)
		return (1);
	tp = exp;
	while (tp != NULL)
	{
		if ((ft_strlen(((t_env *)tp->content)->name) == ft_strlen(name))
			&& !ft_strncmp(((t_env *)tp->content)->name, name, ft_strlen(name)))
		{
			free(((t_env *)tp->content)->info);
			((t_env *)tp->content)->info = add_declare(changed_info);
			return (0);
		}
		tp = tp->next;
	}
	ft_lstadd_back(&exp, ft_lstnew(ft_create_export(changed_info)));
	return (0);
}

void	free_export(t_list *exp)
{
	t_list	*tmp;
	t_list	*tmp_next;

	if (!exp)
		return ;
	tmp = exp;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		free(((t_exp *)tmp->content)->name);
		free(((t_exp *)tmp->content)->info);
		free(tmp->content);
		free(tmp);
		tmp = tmp_next;
	}
}

char	**convert_export(t_minishell *mini)
{
	char	**export;
	t_list	*temp;
	int		i;

	i = 0;
	temp = mini->export;
	export = (char **)malloc(sizeof(char *) * (ft_lstsize(mini->export) + 1));
	while (temp)
	{
		export[i] = ft_strdup(((t_exp *)(temp->content))->info);
		i++;
		temp = temp->next;
	}
	export[i] = 0;
	return (export);
}
