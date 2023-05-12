/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:20:43 by pealexan          #+#    #+#             */
/*   Updated: 2023/05/12 12:45:26 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_home(t_minishell *mini, char *arg)
{
	char	*new;
	char	*temp;

	temp = get_info_env(&mini->env, "HOME");
	new = ft_strjoin(temp, arg + 1);
	return (new);
}

static void	update_env(t_minishell *mini, char *path)
{
	char	*old_pwd;
	char	*temp;
	char	*new_pwd;
	char	*new_path;

	if (path[0] == '~')
		new_path = expand_home(mini, path);
	else if (path[0] == '-')
		new_path = ft_strdup(get_info_env(&mini->env, "OLDPWD"));
	else
		new_path = ft_strdup(path);
	temp = getcwd(0, 0);
	old_pwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	modify_info(mini->env, "OLDPWD", old_pwd);
	modify_export(mini->export, "OLDPWD", old_pwd);
	chdir(new_path);
	free(new_path);
	temp = getcwd(0, 0);
	new_pwd = ft_strjoin("PWD=", temp);
	free(temp);
	modify_info(mini->env, "PWD", new_pwd);
	modify_export(mini->export, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

static void	cd_error(t_minishell *mini, char **cmd_args)
{
	struct stat	statbuf;

	if (cmd_args[1][0] == '~')
		cmd_args[1] = expand_home(mini, cmd_args[1]);
	else if (ft_strlen(cmd_args[1]) == 1 && !ft_strncmp(cmd_args[1], "-", 1))
		cmd_args[1] = ft_strdup(get_info_env(&mini->env, "OLDPWD"));
	if (stat(cmd_args[1], &statbuf) == 0)
	{
		free_child(mini, cmd_args, 0);
		exit (0);
	}
	else if (cmd_args[1][0] == '-' && cmd_args[1][1])
		cd_error2(mini, cmd_args);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
