# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfaustin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 10:58:53 by kfaustin          #+#    #+#              #
#    Updated: 2023/04/14 10:58:55 by kfaustin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name:
NAME	= minishell

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
EFLAGS	= -lreadline
RM		= rm -rf

# Sources, objects and dir
SRCDIR	= ./src/
SRC		= main.c utils.c
OBJ		= $(addprefix $(SRCDIR), $(SRC:.c=.o))

# Libft
LIBDIR	= ./includes/libft/
LIBAFT	= libft.a

all: $(NAME)

$(NAME): $(OBJ) libft
		$(CC) $(CFLAGS) $(LIBAFT) $(OBJ) -o $(NAME) $(EFLAGS)

libft:
		make -C $(LIBDIR)
		cp $(LIBDIR)$(LIBAFT) .

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(LIBAFT)
		$(RM) $(NAME)

re: fclean all
