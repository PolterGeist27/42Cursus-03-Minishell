/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:07:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/12 15:45:14 by diogmart         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_list	*head;

	head = init_env(env);
	modify_info(head, "SSH_AUTH_SOCK", "IT WORKSSSS!!!!");
	ft_printlist(head);
	free_env(head);
	return (0);
}
