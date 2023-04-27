/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:26:16 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/27 08:56:39 by pealexan         ###   ########.fr       */
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

/* typedef struct s_command
{
	char	**args;
	char	*command;
	int		in_fd;
	int		out_fd;
}	t_command; */

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
	pid_t		pid;
}	t_minishell;


typedef struct s_env
{
	char	*name;
	char	*info;
}	t_env;

//error_handling
int	unexpected_tokens(char *input);
int	no_support_operators(char *input);
int	check_quotes(char *input);
int	invalid_syntax(char *input);
int	valid_input(char *input);

//error_handling2
int	syntax_error_operator(char *error, char *operator);
int	syntax_error_token(char *error, char metachar, int dup);
int	unexpected_token_redir(char *input, int *i);

char	*get_info_env(t_list **env, char *name);
void	ft_printlist(t_list *list);
void	add_to_env(t_list **env, char *info);
t_list	*init_env(char **env);
t_env	*ft_create_data(char *info);
char	*get_name(char *info);
int	modify_info(t_list *env, char *name, char *changed_info);
void	free_env(t_list *env);


t_list    *cmd_list(t_minishell *mini, char *input, t_list *env);
char	*get_command(char *arg, t_minishell *mini);
char	*add_whitespaces(char *str);
size_t	ft_meta_strlen(char *str);

int	ft_wordcount_meta(char *str, char c);
char	**split_meta(char *s, char c);

void	input_handler(t_minishell *mini, char *input, t_list *env);

void	execute_single_cmd(t_minishell *mini, t_list *env, char *input);

void	execute_cmd(t_minishell *mini, t_list *env, char *input, int i);


void	execute_multi_cmds(t_minishell *mini, t_list *env);


void	redirect(int a, int b);

char	**handle_redirs(t_minishell *mini, char *input);

void    command_error(char *command);

void	get_prompt(t_env *envinfo, t_minishell *mini);
char	*get_cwd(t_env *envinfo);
void	init_mini(t_minishell *mini, char **env);
void	get_envvariables(t_env *env);

char	*getcommand(char *arg, t_minishell *mini);
char	**parse_input(t_minishell *mini, char *input);

void	shift_redir(char **cmd_args, int *i, int *count);
void	handle_heredoc(char **cmd_args, t_minishell *mini, int *i, int *count);


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
