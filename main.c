/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/26 21:22:02 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO:
	- a lot;
*/

int	main(int argc, char **argv, char **sys_env)
{
	t_list		*env;
	//t_list  	*commands;
	t_env		envinfo;
	t_minishell	mini;
	char		*input;
	int			i;

	(void)argc;
	(void)argv;
	env = init_env(sys_env);
	// pedro :
	//init_mini(&mini, sys_env);
	//get_envvariables(&envinfo);
	while (1)
	{
		i = 0;
		//get_prompt(&envinfo, &mini);
		input = readline(":> ");
		add_history(input);
		if (!valid_input(input))
		{
			free(input);
			continue;
		}
		input_handler(&mini, input, env);
		if (mini.pipe_num > 0)
			execute_multi_cmds(&mini, env);
		else
			execute_single_cmd(&mini, env, add_whitespaces(mini.args[i]));
		waitpid(-1, 0, 0);
		//free(mini.prompt);
		free(input);
	}
	//ft_free_split(mini.paths);
	// end
	free_env(env);
	return (0);
}
