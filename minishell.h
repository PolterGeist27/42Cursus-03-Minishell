/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:26:16 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/21 08:41:58 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "headers/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# define METACHAR "><|"  //no need to replicate or handle \;
# define REDIR "><"
# define GGREATER ">>"
# define LLOWER "<<"
# define NOTHANDLE "&;(){}*\\"


# define UNTOKEN "minishell: syntax error near unexpected token `"
# define NOSUPPORT "minishell: no support for operator `"

typedef struct s_redir
{
	int		*type;
	char	*file;
}	t_redir;

typedef struct s_command
{
	char	*words;
	t_list	*redir;
}	t_command;

typedef	struct s_minishell
{
	char	**args;
	char	**paths;
	char	*prompt;
	int		in_fd;
	int		out_fd;
	int		cmd_num;
	int		pipe_num;
	int		*pipe_fd;
}	t_minishell;


typedef struct s_env
{
	char	*home;
	char	*user;
	char	*local;
}	t_env;

void	get_prompt(t_env *envinfo, t_minishell *mini);
char	*get_cwd(t_env *envinfo);
void	init_mini(t_minishell *mini, char **env);
void	get_envvariables(t_env *env);
void	execute_single_cmd(t_minishell *mini, char *buffer);
char	*getcommand(char *arg, t_minishell *mini);
char	**parse_input(t_minishell *mini, char *input);
void	execute_cmds(t_minishell *mini, char **env);
void	processes(t_minishell *mini, char **env, char *input);
void	close_pipes(t_minishell *mini);
void	open_pipes(t_minishell *mini);
void	split_line(t_minishell *mini, char *buffer);
void	count_pipes(t_minishell *mini, char *buffer);
void	heredoc(char *limiter, t_minishell *mini);
void	init_mini(t_minishell *mini, char **env);


/*
BUILT-INS
	◦ echo with option -n
	◦ cd with only a relative or absolute path
	◦ pwd with no options
	◦ export with no options
	◦ unset with no options
	◦ env with no options or arguments
	◦ exit with no options

SHORTCUTS
	◦ ctrl-C displays a new prompt on a new line.
	◦ ctrl-D exits the shell.
	◦ ctrl-\ does nothing.

REDIRECTIONS
	◦ < should redirect input.
	◦ > should redirect output.
	◦ << should be given a delimiter, then read the input until a line containing the
		delimiter is seen. However, it doesn’t have to update the history!
	◦ >> should redirect output in append mode.

PIPES
	Implement pipes (| character)
*/

#endif
