/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:39 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/19 12:38:31 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	putstring_exit(char *str, int flag)
{
	ft_putstr_fd(str, 2);
	exit(flag);
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
	char	*tmp4;

	tmp1 = ft_strjoin(root->user, "@");
	tmp2 = ft_strjoin(root->s_manager, ":");
	tmp3 = ft_strjoin(tmp1, tmp2);
	tmp4 = ft_strjoin(root->path, "$ ");
	root->prompt = ft_strjoin(tmp3, tmp4);
	free (tmp1);
	free (tmp2);
	free (tmp3);
	free (tmp4);
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
	free (root->user);
	free (root->s_manager);
	free (root->home);
	free (root->path);
	return (root->prompt);
}
