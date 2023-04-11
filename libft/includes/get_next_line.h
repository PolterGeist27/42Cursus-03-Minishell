/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:50:29 by diogmart          #+#    #+#             */
/*   Updated: 2022/11/22 15:00:38 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

//	 MAX_FILES_OPENED is the maximum file descriptor per process
//	 obtained through the command "ulimit -a"
# ifndef MAX_FILES_OPENED
#  define MAX_FILES_OPENED 1024
# endif

//	Value can be changed at compile time
//	by adding "-D BUFFER_SIZE=n" to the compiler call
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//  get_next_line.c
char	*get_next_line(int fd);

#endif
