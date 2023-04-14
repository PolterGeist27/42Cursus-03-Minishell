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

static char *ft_move_ptr(char *s1, char *s2)
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
}

void	display_app_prompt(t_root *root)
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
}