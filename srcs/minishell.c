/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/14 11:11:29 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
TODO:
	- a lot;
*/

void	ft_printlist(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp != NULL)
	{
		printf("%s\n", ((t_env *)(tmp->content))->info);
		tmp = tmp->next;
	}
}

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
