# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/04/11 12:10:57 by diogmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a

#----------DIRS----------#
SRCDIR = ./srcs/
LIBFTDIR = ./libft/
INCDIR = ./includes/

SRC = 

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

OBJS = ${SRC:.c=.o}

#---------RULES---------#
.c.o:
			$(CC) $(CFLAGS) -c -I$(INCDIR) $< -o ${<:.c=.o}

all: 		$(NAME)

$(LIBFT):
			cd $(LIBFTDIR) && $(MAKE)

$(NAME): 	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
		@$(RM) $(OBJ) $(BONUS_OBJ)
			@cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
			$(RM) $(NAME) $(BONUS) $(LIBFT)
			cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all
