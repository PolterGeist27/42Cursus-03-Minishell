/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:37:33 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/19 10:39:58 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value_from_key(t_env *header, char *key)
{
	t_env	*tmp;
	char	*str;

	tmp = header;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)) == 0)
		{
			str = ft_strdup(tmp->value);
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
