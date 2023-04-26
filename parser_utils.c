/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:18:50 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/26 12:19:47 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_meta_strlen(char *str)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strchr(METACHAR, str[i]))
		{
			len += 3;
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

int is_builtin(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (ft_strncmp(name, "echo", len) == 0)
		return (1);
	if (ft_strncmp(name, "cd", len) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", len) == 0)
		return (1);
	if (ft_strncmp(name, "export", len) == 0)
		return (1);
	if (ft_strncmp(name, "unset", len) == 0)
		return (1);
	if (ft_strncmp(name, "env", len) == 0)
		return (1);
	if (ft_strncmp(name, "exit", len) == 0)
		return (1);
	return (0);
}
