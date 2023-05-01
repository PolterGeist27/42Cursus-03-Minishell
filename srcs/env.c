/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:17:16 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/01 14:38:16 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_env(char **env)
{
	int		i;
	t_list	*head;
	t_list	*tmp;

	i = 0;
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(ft_create_data(env[i])));
	tmp = head;
	i++;
	while (env[i] != NULL)
	{
		tmp->next = ft_lstnew(ft_create_data(env[i]));
		tmp = tmp->next;
		i++;
	}
	return (head);
}

t_env	*ft_create_data(char *info)
{
	t_env	*data;

	data = (t_env *)malloc(sizeof(t_env));
	data->name = get_name(info);
	data->info = ft_strdup(info);
	return (data);
}

char	*get_name(char *info)
{
	char	*name;
	int		size;

	size = 0;
	while (info[size] != '=')
		size++;
	name = (char *)malloc(sizeof(char) * size + 1);
	ft_strlcpy(name, info, size + 1);
	return (name);
}

int	modify_info(t_list *env, char *name, char *changed_info)
{
	t_list	*tmp;
	char	*new_name;

	if (!env)
		return (1);
	tmp = env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(((t_env *)tmp->content)->name, name, ft_strlen(name)))
		{
			free(((t_env *)tmp->content)->info);
			new_name = ft_strjoin(name, "=");
			((t_env *)tmp->content)->info = ft_strdup(changed_info);
			free(new_name);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&env, ft_lstnew(ft_create_data(changed_info)));
	return (0);
}

void	free_env(t_list *env)
{
	t_list	*tmp;
	t_list	*tmp_next;

	if (!env)
		return ;
	tmp = env;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		free(((t_env *)tmp->content)->name);
		free(((t_env *)tmp->content)->info);
		free(tmp->content);
		free(tmp);
		tmp = tmp_next;
	}
}
