/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/02 15:49:43 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **sys_env)
{
	t_minishell	mini;
	int			i;	

	(void)argv;
	if (argc > 1)
		printf("minishell: wrong number of arguments\n");
	else
	{
		mini.env = init_env(sys_env);
		while (1)
		{
			i = 0;
			signal_handling();
			i = read_input(&mini);
			if (!i)
				continue ;
			else if (i == -1)
				break ;
			executer(&mini);
			free_main(&mini, 0);
		}
		return (free_env(mini.env), ft_putstr("exit\n"), 0);
	}
	return (0);
}
