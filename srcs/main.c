/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/02 11:31:42 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **sys_env)
{
	t_minishell	mini;

	(void)argv;
	signal_handling();
	if (argc == 1)
	{
		signal(SIGINT, &handler);
		mini.env = init_env(sys_env);
		while (1)
		{
			if (!read_input(&mini))
				continue ;
			executer(&mini);
			get_exit_status();
			free_main(&mini, 0);
		}
	}
	return (0);
}
