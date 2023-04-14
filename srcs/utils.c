/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:59:10 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/14 11:09:03 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(t_list **env, char *info)
{
	t_list *new;

	new = ft_lstnew(ft_create_data(info));
	ft_lstadd_back(env, new);
}