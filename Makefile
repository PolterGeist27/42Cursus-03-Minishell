# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/04/28 14:26:05 by pealexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a

#----------DIRS----------#
SRCDIR = ./srcs/
LIBFTDIR = ./libft/
INCDIR = ./includes/

#----------SRCS----------#
SRC =	env_utils \
		env \
		error_handling \
		error_handling2 \
		executer_utils \
		executer \
		expander \
		handle_heredoc \
		handle_redirs \
		input_handler \
		main \
		parser_utils \
		split_meta \

SRCS = $(addprefix ${SRCDIR}, $(addsuffix .c, ${SRC}))

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCDIR)
EXTRA = -lreadline
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
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFTDIR)$(LIBFT) $(EXTRA) -o $(NAME)

clean:
			@$(RM) $(OBJS) $(BONUS_OBJ)
			@cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
			@$(RM) $(NAME) $(BONUS) $(LIBFT)
			@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all
