/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/12 12:38:50 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
TODO:
	- free env;

*/

void	ft_printlist(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp != NULL)
	{
		printf("%s\n", ((t_env *)(tmp->content))->raw);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_printlist(init_env(env));
	return (0);
}
