/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:11:56 by kfaustin          #+#    #+#             */
/*   Updated: 2023/04/11 13:47:14 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*move_pointer(char *s1, char *s2)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (s1[i] == s2[i])
		i++;
	while (j++ < i)
		s1++;
	return (s1);
}

int	main(int argc, char **argv)
{
	t_root	root;
	char	*pwd;
	int	i = 0;

	(void)argc;
	(void)argv;
	root.user = getenv("USER");
	root.home = getenv("HOME");
	root.local = getenv("SESSION_MANAGER");

	printf("User: %s\nHome: %s\nLocal: %s\n\n", root.user, root.home, root.local);
	while (*root.local != '/')
		root.local++;
	root.local++;
	while (root.local[i] != '.')
		i++;
	root.local[i] = '\0';
	pwd = getcwd(NULL, 0);
	printf("pwd: %s\n\n", pwd);
	printf("%s@%s:~%s\n", root.user, root.local, move_pointer(pwd, root.home));
	return (0);
}
