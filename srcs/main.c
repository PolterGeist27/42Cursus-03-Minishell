/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/19 14:31:27 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
TODO:
	- a lot;
*/

int	main(int argc, char **argv, char **sys_env)
{
	t_list		*env;
	t_env		envinfo;
	t_minishell	mini;
	char		*buffer;

	(void)argc;
	(void)argv;
	env = init_env(sys_env);
	// pedro :
	init_mini(&mini, sys_env);
	get_envvariables(&envinfo);
	while (1)
	{
		get_prompt(&envinfo, &mini);
		buffer = readline(mini.prompt);
		add_history(buffer);
		//split_line(&mini, buffer);
		/* if (mini.pipe_num > 0)
			execute_cmds(&mini, buffer); */
		//else
		execute_single_cmd(&mini, buffer);
		wait(0);
		free(mini.prompt);
		free(buffer);
	}
	//ft_free_split(mini.paths);
	// end
	free_env(env);
	
	return (0);
}
