# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/04/11 10:31:00 by fvalli-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a

#----------DIRS----------#
SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/

SRC = minishell.c

#--------COMMANDS--------#
CC = clang
CFLAGS = -Wall -Wextra -Werror
EXTRA = -pthread -lreadline
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#---------RULES---------#
.c.o:
			$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}

all: 		$(NAME)

$(LIBFT):
			cd $(LIBFTDIR) && $(MAKE)

$(NAME): 	$(OBJ) $(LIBFT) $(MLX)
			$(CC) $(CFLAGS) $(EXTRA) $(OBJ) $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)
			@cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
			@$(RM) $(NAME) $(BONUS) $(LIBFT)
			@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all
