/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/19 13:44:18 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_root	root;

	(void)argc;
	(void)argv;
	(void)env;
	env_to_list(&root, env);
	while (1)
	{
		input = readline(display_prompt(&root));
		printf("%s\n", input);
		if (!input)
		{
			free (input);
			break ;
		}
	}
	while (root.list)
	{
		printf("(%d): %s - %s\n", root.list->index, root.list->key, root.list->value);
		root.list = root.list->next;
	}
	return (0);
}
