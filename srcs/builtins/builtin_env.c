/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:09:14 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/30 17:29:54 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_minishell *mini, char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("env: No options or arguments supported\n", 2);
		free_child(mini, cmd_args, 0);
		g_exit_status = 1;
		exit (1);
	}
	ft_printlist(mini->env);
	free_child(mini, cmd_args, 0);
	g_exit_status = 0;
	exit (0);
}
