# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/04/20 15:37:46 by diogmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a

#----------DIRS----------#
SRCDIR = ./srcs/
LIBFTDIR = ./libft/
INCDIR = ./includes/

#----------SRCS----------#
SRC =	main \
		echo \
		env \
		env_utils \
		dir \
		minishell \
		prompt \

SRCS = $(addprefix ${SRCDIR}, $(addsuffix .c, ${SRC}))

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCDIR)
AR = ar rcs
RM = rm -rf
MAKEFLAGS += --no-print-directory

#----------OBJS----------#
OBJS = ${SRCS:.c=.o}

#---------COLORS---------#
GREEN       =   \033[0;32m


#---------RULES---------#

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: 		$(NAME)
	@echo "$(GREEN)[Compiled Minishell]"

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE)

$(NAME): 	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
			@$(RM) $(OBJS) $(BONUS_OBJ)
			@cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
			@$(RM) $(NAME) $(BONUS) $(LIBFT)
			@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all
