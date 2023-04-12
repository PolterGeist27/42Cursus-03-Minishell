/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:26:16 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/12 12:37:00 by diogmart         ###   ########.fr       */
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

typedef struct s_env_info
{
	char	*home;
	char	*user;
	char	*local;
}	t_env_info;

typedef struct s_env
{
	char	*name;
	char	*info;
	char	*raw;
}	t_env;

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

//	echo.c
void	echo(char *arg, int flag);

//	env.c
t_list	*init_env(char **env);
t_env	*ft_create_data(char *raw);
char	*get_name(char *raw);

#endif
