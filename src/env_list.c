/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:27:09 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/19 14:04:49 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_key_value(char **key, char **value, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = ft_substr(str, 0, i);
	*value = ft_substr(str, (i + 1), ft_strlen(str) - i);
}

static void	init_env_node(t_env **node, char **key, char **value, int i)
{
	*node = (t_env *)malloc(sizeof(t_env));
	if (!(*node))
		putstring_exit("Error: Malloc of *node fails\n", 1);
	(*node)->index = i;
	(*node)->key = *key;
	(*node)->value = *value;
	(*node)->next = NULL;
}

static void	stack_env_list(t_root *root, t_env *node)
{
	t_env	*header;

	if (!root->list)
	{
		root->list = node;
		return ;
	}
	header = root->list;
	while (root->list->next != NULL)
		root->list = root->list->next;
	root->list->next = node;
	root->list = header;
}

void	env_to_list(t_root *root, char **env)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;

	if (!env)
		putstring_exit("Error: env is NULL\n", 1);
	i = -1;
	root->list = NULL;
	while (env[++i])
	{
		init_key_value(&key, &value, env[i]);
		init_env_node(&node, &key, &value, i);
		stack_env_list(root, node);
	}
}