/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:26:16 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 18:19:00 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

typedef struct s_minishell
{
	char	**args;
	char	**paths;
	char	*prompt;
	int		in_fd;
	int		out_fd;
	int		cmd_num;
	int		pipe_num;
	int		*pipe_fd;
	pid_t	pid;
	t_list	*env;
	int		counter;
}	t_minishell;

typedef struct s_env
{
	char	*name;
	char	*info;
}	t_env;

/*ENV_UTILS-------------------------------------------------------------------*/

/// @brief Searches the list for @param name and returns its information
/// @param env 
/// @param name 
/// @return A char * of the information after the '='
char	*get_info_env(t_list **env, char *name);

/// @brief Prints the env list
/// @param list 
void	ft_printlist(t_list *list);

/// @brief Adds a new node to env, same as export
/// @param env 
/// @param info 
void	add_to_env(t_list **env, char *info);

/*ENV-------------------------------------------------------------------------*/

/// @brief Initializes the env list
/// @param env 
/// @return Head of the list
t_list	*init_env(char **env);

/// @brief Creates a node for the list
/// @param info 
/// @return The new node
t_env	*ft_create_data(char *info);

/// @brief Parses info in search of '=', copies the string before the '='
/// @param info 
/// @return The string before '='
char	*get_name(char *info);

/// @brief Alters a node pointed by name and changes its info. Same as export
/// @param env 
/// @param name 
/// @param changed_info 
/// @return 0 on success, 1 if there's no list
int		modify_info(t_list *env, char *name, char *changed_info);

/// @brief Cleans all allocated memory for the list
/// @param env 
void	free_env(t_list *env);

/*ERROR_HANDLING--------------------------------------------------------------*/

/// @brief Passes input through several validity checks
/// @param input 
/// @return 0 if not valid, 1 if valid
int		valid_input(char *input);

/// @brief Checks simple syntax like, metacharacter on start or end of input
/// @param input 
/// @return 1 if not valid, 0 if valid
int		invalid_syntax(char *input);

/// @brief Checks if there are any unclosed quotes
/// @param input 
/// @return 1 if unclosed quptes, 0 if valid
int		check_quotes(char *input);

/// @brief Checks input for operators that are not supported by the scope of
/// the project
/// @param input 
/// @return 1 if not valid, 0 if valid
int		no_support_operators(char *input);

/// @brief Checks input for any unexpeteced token errors like in bash
/// @param input 
/// @return 1 if not valid, 0 if valid
int		unexpected_tokens(char *input);

/*ERROR_HANDLING2-------------------------------------------------------------*/

/// @brief Prints the error message pointed to by @param error and the its
/// respective @param operator
/// @param error 
/// @param operator
/// @return 1 to signify not valid
int		syntax_error_operator(char *error, char *operator);

/// @brief Prints the error message pointed to by @param error and the its
/// respective @param metachar, if @param dup, prints @param metachar twice
/// @param error 
/// @param metachar 
/// @param dup 
/// @return 1 to signify not valid
int		syntax_error_token(char *error, char metachar, int dup);

/// @brief Checks input for unexpected tokens tied to redirections
/// @param input 
/// @param i 
/// @return 1 if not valid, 0 if valid
int		unexpected_token_redir(char *input, int *i);

/*EXECUTER_UTILS--------------------------------------------------------------*/

/// @brief Prints command not found error, sets exit_status to 127
/// @param command
void	command_error(char *command);

/// @brief Opens all necessary pipes
/// @param	mini
void	open_pipes(t_minishell *mini);

/// @brief Closes all pipes so they are not listening for information
/// @param mini
void	close_pipes(t_minishell *mini);

/// @brief Handles redirections accordingly to the order of pipes
/// @param mini 
/// @param i 
void	redirections(t_minishell *mini, int i);

/// @brief Redirects input by using dup2
/// @param a
/// @param b
void	redirect(int a, int b);

/*EXECUTER--------------------------------------------------------------------*/

/// @brief Uses the PATH env variable to check if user can execute the specified
/// command
/// @param arg
/// @param mini
/// @return The command that can be executed, if no command is found return 0
char	*get_command(char *arg, t_minishell *mini);

/// @brief Executes piped commands, first redirects accordingly and then checks 
/// for a valid command and uses execve to execute it
/// @param mini
/// @param env
/// @param input
/// @param i
void	execute_cmd(t_minishell *mini, t_list *env, char *input, int i);

/// @brief Creates all necessary pipes, opens them and passes arguments to 
/// execute_cmd
/// @param mini
/// @param env
/// @param input
/// @param i
void	execute_multi_cmds(t_minishell *mini, t_list *env);

/// @brief Executes when there are no pipes, first redirects accordingly and 
/// then checks for a valid command and uses execve to execute it 
/// @param mini
/// @param env
/// @param input
void	execute_single_cmd(t_minishell *mini, t_list *env, char *input);

/// @brief Checks if there are any pipes to call the respective function
/// @param mini
/// @param env
void	executer(t_minishell *mini, t_list *env);

/*EXPANDER--------------------------------------------------------------------*/

/// @brief Checks arg for any '$' and expands the variable to the respective
/// value found in env, takes quotes into consideration.
/// Expansion does not happen if '$' is found between single quotes.
/// @param arg 
/// @param mini 
/// @return A new string with the epanded variables from env
char	*expander(char *arg, t_minishell *mini);

/*HANDLE_HEREDOC--------------------------------------------------------------*/

/// @brief Handles the here_doc functionality similarly to bash
/// @param cmd_args
/// @param mini
/// @param i
/// @param count
void	handle_heredoc(char **cmd_args, t_minishell *mini, int *i, int *count);

/*HANDLE_REDIRS---------------------------------------------------------------*/

/// @brief Shifts @param cmd_args accordingly, removing all redirections from it
/// @param cmd_args
/// @param i
/// @param count
void	shift_redir(char **cmd_args, int *i, int *count);

/// @brief Splits input accordingly and then parses each char* to check if any 
/// redirections need to be done, calls the respective function for each case
/// @param mini
/// @param input
/// @return The result of the split input without any possible redirections
char	**handle_redirs(t_minishell *mini, char *input);

/*INPUT_HANDLER---------------------------------------------------------------*/

/// @brief Initializes the needed values for the struct mini
/// @param mini
/// @param input
/// @param env
void	input_handler(t_minishell *mini, char *input, t_list *env);

/// @brief Reads the input by using readline
/// @param mini
/// @param env
/// @return 0 if no valid input, 1 if valid 
int		read_input(t_minishell *mini, t_list *env);

/*PARSER_UTILS----------------------------------------------------------------*/

/// @brief Adds whitespaces before and after any redirection operator
/// @param str
/// @return The string with the added whitespaces
char	*add_whitespaces(char *str);

/// @brief Counts the strlen of str and adds +3 if any redir is found
/// @param str
/// @return The final size of the string
size_t	ft_meta_strlen(char *str);

/// @brief Checks @param name to see if the command is a built-in
/// @param name
/// @return 1 if it is a built-in, 0 if not
int		is_builtin(char *name);

/*SPLIT_META------------------------------------------------------------------*/

/// @brief Counts the amonut of words that exist in @param str, takes quotes 
/// into account
/// @param str 
/// @param c 
/// @return Number of words
int		ft_wordcount_meta(char *str, char c);

/// @brief Splits @param s by @param c, takes quotes into account
/// @param s 
/// @param c 
/// @return The matrix of all the words
char	**split_meta(char *s, char c);

/*UTILS-----------------------------------------------------------------------*/

/// @brief Checks the quote value and modifies it accordingly
/// @param c 
/// @param quote 
/// @return New quote value
char	quote_value(char c, char quote);

/// @brief Checks @param c to see if is a digit or a letter, or '_'
/// @param c 
/// @return 1 if true
int		isalnumextra(int c);

#endif
