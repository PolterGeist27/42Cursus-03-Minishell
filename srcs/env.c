/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:17:16 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/12 12:40:26 by diogmart         ###   ########.fr       */
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
	ft_lstadd_back(&head ,ft_lstnew(ft_create_data(env[i])));
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

t_env	*ft_create_data(char *raw)
{
	t_env	*data;

	data = (t_env *)malloc(sizeof(t_env));
	data->raw = ft_strdup(raw);
	data->name = get_name(raw);
	data->info = ft_strchr(raw, '=') + 1;
	return (data);
}

char	*get_name(char *raw)
{
	char	*name;
	int		size;

	size = 0;
	while (raw[size] != '=')
		size++;
	name = (char *)malloc(sizeof(char) * size);
	ft_strlcpy(name, raw, size);
	return (name);
}
