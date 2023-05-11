# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/05/11 12:55:59 by pealexan         ###   ########.fr        #
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
		errors \
		executer_builtin \
		executer_utils \
		executer \
		expander \
		export \
		handle_heredoc \
		handle_redirs \
		input_handler \
		main \
		quote_remover \
		signals \
		split_meta \
		utils \
		utils2 \
		builtins/builtin_cd \
		builtins/builtin_echo \
		builtins/builtin_env \
		builtins/builtin_exit \
		builtins/builtin_export \
		builtins/builtin_export2 \
		builtins/builtin_pwd \
		builtins/builtin_unset \

SRCS = $(addprefix ${SRCDIR}, $(addsuffix .c, ${SRC}))

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCDIR) -g -fsanitize=address
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
	@mkdir -p bin/$(dir $<)
	@$(CC) $(CFLAGS) -c $< -o bin/$*.o

all: 		$(NAME)
	@echo "$(GREEN)[Compiled Minishell]"

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE)

$(NAME): 	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS:%=bin/%) $(LIBFTDIR)$(LIBFT) $(EXTRA) -o $(NAME)

clean:
			@$(RM) bin
			@cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
			@$(RM) $(NAME) $(BONUS)
			@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all
