/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:20:55 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/21 14:22:13 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	builtins_echo(t_tokens *tokens)
{
	if (tokens->flag && !ft_strncmp(tokens->flag, "-n", 3))
	{
		ft_putstr_fd(tokens->complement, STDOUT_FILENO);
	}
	if (!tokens->flag)

}
