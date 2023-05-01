/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:20:43 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/01 14:33:19 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_env(t_minishell *mini, char *path)
{
	char	*old_pwd;
	char	*temp;
	char	*new_pwd;

	temp = getcwd(0, 0);
	old_pwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	modify_info(mini->env, "OLDPWD", old_pwd);
	chdir(path);
	temp = getcwd(0, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	modify_info(mini->env, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

static void	cd_error(t_minishell *mini, char **cmd_args)
{
	struct stat	statbuf;

	if (stat(cmd_args[1], &statbuf) == 0)
	{
		g_exit_status = 0;
		free_child(mini, cmd_args, 0);
		exit (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		free_child(mini, cmd_args, 0);
		exit (1);
	}
}

void	check_cd(t_minishell *mini, char **cmd_args)
{
	int		status;
	int		i;

	i = 0;
	while (cmd_args[i])
		i++;
	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status == 0)
	{
		if (i == 1)
			update_env(mini, get_info_env(&mini->env, "HOME"));
		else
			update_env(mini, cmd_args[1]);
	}
}

void	builtin_cd(t_minishell *mini, char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		free_child(mini, cmd_args, 0);
		exit (1);
	}
	else if (i == 1)
	{
		g_exit_status = 0;
		free_child(mini, cmd_args, 0);
		exit (0);
	}
	else
		cd_error(mini, cmd_args);
}
