/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:43:47 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 08:54:16 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_envvariables(t_env *envinfo)
{
	int	i;

	i = 0;	
	envinfo->user = getenv("USER");
	envinfo->home = getenv("HOME");
	envinfo->local = getenv("SESSION_MANAGER");
	while (*envinfo->local != '/')
		envinfo->local++;
	*envinfo->local = '@';
	while (envinfo->local[i] != '.' && envinfo->local[i] != ':')
		i++;
	envinfo->local[i] = ':';
	envinfo->local[i + 1] = '\0';
}

char	*get_cwd(t_env *envinfo)
{
	char	*cwd;
	char	*trimcwd;
	int		i;

	i = 0;
	cwd = getcwd(0, 0);
	while (cwd[i] == envinfo->home[i])
		i++;
	cwd[i - 1] = '~';
	trimcwd = ft_strdup(cwd + i - 1);
	free(cwd);
	return (trimcwd);
}

void	get_prompt(t_env *envinfo, t_minishell *mini)
{
	char	*temp;
	char	*cwd;

    mini->prompt = ft_strdup("");
	temp = ft_strdup(mini->prompt);
	free(mini->prompt);
	mini->prompt = ft_strjoin(temp, envinfo->user);
	free(temp);
	temp = ft_strdup(mini->prompt);
	free(mini->prompt);
	mini->prompt = ft_strjoin(temp, envinfo->local);
	free(temp);
	cwd = get_cwd(envinfo);
	temp = ft_strdup(mini->prompt);
	free(mini->prompt);
	mini->prompt = ft_strjoin(temp, cwd);
	free(temp);
	free(cwd);
	temp = ft_strdup(mini->prompt);
	free(mini->prompt);
	mini->prompt = ft_strjoin(temp, "$ ");
	free(temp);
}