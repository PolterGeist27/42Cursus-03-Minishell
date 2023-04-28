/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/28 08:57:43 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **sys_env)
{
	t_list		*env;
	t_minishell	mini;
	pid_t			i;
	int			status;

	if (argc == 1)
	{
		(void)argv;
		while (1)
		{
			i = 1;
			env = init_env(sys_env);
			if (!read_input(&mini, env))
				continue;
			executer(&mini, env);
			while (i > 0)
				i = wait(&status);
			ft_free_split(mini.paths);
			ft_free_split(mini.args);
			free_env(env);
		}
	}
	return (0);
}
