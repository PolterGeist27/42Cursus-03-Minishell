/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:19 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **sys_env)
{
	t_list		*env;
	t_env		envinfo;
	t_minishell	mini;
	char		*input;
	pid_t			i;
	int			status;

	if (argc == 1)
	{
		(void)argv;
		env = init_env(sys_env);
		//get_envvariables(&envinfo);
		while (1)
		{
			i = 1;
			//get_prompt(&envinfo, &mini);
			input = readline(":> ");
			if (ft_strlen(input) > 0)
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
				execute_single_cmd(&mini, env, add_whitespaces(mini.args[0]));
			while (i > 0)
				i = wait(&status);
			//free(mini.prompt);
			free(input);
		}
		//ft_free_split(mini.paths);
		// end
		free_env(env);
	}
	return (0);
}
