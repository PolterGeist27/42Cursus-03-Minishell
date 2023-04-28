/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:52:05 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/19 14:32:41 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int		cd(t_list **env, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_info_env(env, "PWD");
	if (chdir(path))
		return (1);
	modify_info(*env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	modify_info(*env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int		pwd(t_list **env)
{
	char	*path;

	path = get_info_env(env, "PWD");
	return(printf("%s\n", path));
}
