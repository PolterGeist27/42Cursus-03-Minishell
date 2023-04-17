/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/13 15:01:19 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static char *ft_move_ptr(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	while (j++ < i)
		s1++;
	return (s1);
}*/

/*void	display_app_prompt(t_root *root, char **env)
{
	int		i;
	char	*path;

	root->user = getenv("USER");
	root->home = getenv("HOME");
	root->local = getenv("SESSION_MANAGER");
	while (*root->local != '/')
		root->local++;
	i = 0;
	while (root->local[i] != '.')
		i++;
	root->local[i] = '\0';
	path = getcwd(NULL, 0);
	printf("%s@%s:~%s", root->user, root->local, ft_move_ptr(path, root->home));
	free (path);
}*/

void	putstring_exit(char *str, int flag)
{
	ft_putstr_fd(str, 2);
	exit(flag);
}

static void	init_key_value(char **key, char **value, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = ft_substr(str, 0, i);
	*value = ft_substr(str, (i + 1), ft_strlen(str) - i);
}

static void	init_env_node(t_env **node, char *key, char *value, int i)
{
	*node = (t_env *)malloc(sizeof(t_env));
	if (!(*node))
		putstring_exit("Error: Malloc of *node fails\n", 1);
	(*node)->index = i;
	(*node)->key = key;
	(*node)->value = value;
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
		init_env_node(&node, key, value, i);
		stack_env_list(root, node);
	}
}

char	*get_value_from_key(t_env *header, char *key)
{
	t_env	*tmp;
	char	*str;

	tmp = header;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, (ft_strlen(key) + 1)) == 0)
		{
			str = ft_strdup(tmp->value);
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	deal_root_env(t_root *root)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (root->s_manager[i] != '/')
		i++;
	j = 0;
	while (root->s_manager[j] != '.' || root->s_manager[j] != ':')
		j++;
	tmp = ft_substr(root->s_manager, (i + 1), (j - (i + 1)));
	free (root->s_manager);
	root->s_manager = tmp;
	i = 0;
	while (root->home[i] == root->path[i])
		i++;
	tmp = ft_substr(root->path, i, (ft_strlen(root->path) - i));
	free (root->path);
	root->path = tmp;
}

char	*display_prompt(t_root *root)
{
	char	*tmp;
	root->user = get_value_from_key(root->list, "USER");
	root->s_manager = get_value_from_key(root->list, "SESSION_MANAGER");
	root->home = get_value_from_key(root->list, "HOME");
	root->path = getcwd(NULL, 0);
	deal_root_env(root);
	root->prompt = ft_strjoin(root->user, "@");
	tmp = ft_strjoin(root->prompt, root->s_manager);
	free (root->prompt);
	root->prompt = tmp;
	tmp = ft_strjoin(root->prompt, ":~");
	free (root->prompt);
	root->prompt = tmp;
	tmp = ft_strjoin(root->prompt, root->path);
	free (root->prompt);
	root->prompt = tmp;
	return (root->prompt);
}
