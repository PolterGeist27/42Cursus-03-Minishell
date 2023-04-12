/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:58:13 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/11 13:42:14 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		cd(char *path)
{
	return (chdir(path));
}

int		pwd(t_env *env)
{
	char *path;

	path = getenv("PWD");
	return(printf("%s\n", path));
}
