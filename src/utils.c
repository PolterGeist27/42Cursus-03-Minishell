/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/19 15:35:13 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	putstring_exit(char *str, int flag)
{
	ft_putstr_fd(str, 2);
	exit(flag);
}

void	free_t_env(t_env *list)
{
	t_env *header;

	while (list)
	{
		header = list->next;
		free (list->key);
		free (list->value);
		free (list);
		list = header;
	}
}

void	free_t_root(t_root *root)
{
	free (root->prompt);
	free (root->user);
	free (root->s_manager);
	free (root->home);
	free (root->path);
}

static void	s_manager_prompt(t_root *root)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (root->s_manager[i] != '/')
		i++;
	j = 0;
	while (root->s_manager[j] != '.' && root->s_manager[j] != ':')
		j++;
	tmp = ft_substr(root->s_manager, (i + 1), (j - (i + 1)));
	free (root->s_manager);
	root->s_manager = tmp;
}

static void	path_prompt(t_root *root)
{
	int		len_path;
	int		len_home;
	char	*tmp;

	len_path = (int)ft_strlen(root->path);
	len_home = (int)ft_strlen(root->home);
	if ((len_home == len_path) && !(ft_strncmp(root->home, root->path, len_home)))
	{
		free (root->path);
		root->path = ft_strdup("~");
		return ;
	}
	if ((len_home < len_path) && !(ft_strncmp(root->home, root->path, len_home)))
	{
		tmp = ft_substr(root->path, len_home, (len_path - len_home));
		free (root->path);
		root->path = ft_strjoin("~", tmp);
		free (tmp);
		return ;
	}
	if ((len_home > len_path) && !ft_strncmp(root->path, root->home, len_path))
		return ;
	free (root->path);
	root->path = NULL;
}

static void	prompt_prompt(t_root *root)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strjoin(root->user, "@");
	tmp2 = ft_strjoin(root->s_manager, ":");
	tmp3 = ft_strjoin(tmp1, tmp2);
	free (tmp1);
	free (tmp2);
	tmp1 = ft_strjoin(root->path, "$ ");
	root->prompt = ft_strjoin(tmp3, tmp1);
	free (tmp3);
	free (tmp1);

	/*
	int		i;
	int		j;
	free(root->prompt);
	root->prompt = (char *)malloc(sizeof(char)
			* (((ft_strlen(root->user) + 1)
			+ (ft_strlen(root->s_manager) + 1)
			+ (ft_strlen(root->path) + 1)) + 3));
	i = 0;
	j = 0;
	while (root->user[j])
		root->prompt[i++] = root->user[j++];
	root->prompt[i] = '@';
	j = 0;
	while (root->s_manager[j])
		root->prompt[i++] = root->s_manager[j++];
	root->prompt[i] = ':';
	j = 0;
	while (root->path[j])
		root->prompt[i++] = root->path[j++];
	root->path[i++] = '$';
	root->path[i++] = ' ';
	root->path[i] = '\0';*/
}

char	*display_prompt(t_root *root)
{
	root->user = get_value_from_key(root->list, "USER");
	root->s_manager = get_value_from_key(root->list, "SESSION_MANAGER");
	root->home = get_value_from_key(root->list, "HOME");
	root->path = getcwd(NULL, 0);
	s_manager_prompt(root);
	path_prompt(root);
	if (!root->path)
		putstring_exit("Error: Path prompt is NULL\n", 1);
	prompt_prompt(root);
	return (root->prompt);
}
