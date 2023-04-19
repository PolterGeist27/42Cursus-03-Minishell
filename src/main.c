/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:57:37 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/19 15:41:44 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_root	root;
	t_env	*header;

	(void)argc;
	(void)argv;
	(void)env;
	(void)input;
	(void)header;
	env_to_list(&root, env);
	root.prompt = NULL;
	while (1)
	{
		input = readline(display_prompt(&root));
		printf("%s\n", input);
		if (!input)
		{
			free (input);
			break ;
		}
		free (input);
		free_t_root(&root);
	}
	header = root.list;
	while (root.list)
	{
		printf("(%d): %s - %s\n", root.list->index, root.list->key, root.list->value);
		root.list = root.list->next;
	}
	root.list = header;
	free_t_env(root.list);
	free_t_root(&root);
	return (0);
}
