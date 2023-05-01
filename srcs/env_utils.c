/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:59:10 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/01 10:22:29 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_env(t_list **env, char *info)
{
	t_list	*new;

	new = ft_lstnew(ft_create_data(info));
	ft_lstadd_back(env, new);
}

void	ft_printlist(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		printf("%s\n", ((t_env *)(tmp->content))->info);
		tmp = tmp->next;
	}
}

char	*get_info_env(t_list **env, char *name)
{
	char	*info;
	t_list	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(name, ((t_env *)(tmp->content))->name,
			ft_strlen(((t_env *)(tmp->content))->name)))
		{
			info = ft_strchr(((t_env *)(tmp->content))->info, '=');
			info++;
			return (info);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
