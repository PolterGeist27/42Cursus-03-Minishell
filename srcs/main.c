/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/14 12:20:16 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
TODO:
	- a lot;
*/

int	main(int argc, char **argv, char **sys_env)
{
	(void)argc;
	(void)argv;
	t_list	*env;

	env = init_env(sys_env);
	modify_info(env, "SSH_AUTH_SOCK", "IT WORKSSSS!!!!");
	add_to_env(&env, "TEST=24671");
	add_to_env(&env, "TEST2=Atuamae");
	ft_printlist(env);
	free_env(env);
	return (0);
}
