/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/28 20:17:20 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **sys_env)
{
	t_minishell	mini;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			mini.env = init_env(sys_env);
			if (!read_input(&mini))
				continue ;
			executer(&mini);
			get_exit_status();
			ft_free_split(mini.paths);
			ft_free_split(mini.args);
			free_env(mini.env);
		}
	}
	return (0);
}
