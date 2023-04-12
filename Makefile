# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 12:26:28 by pealexan          #+#    #+#              #
#    Updated: 2023/04/11 15:51:15 by diogmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a

#----------DIRS----------#
SRCDIR = ./srcs/
LIBFTDIR = ./libft/
INCDIR = ./includes/

SRC =	minishell \
		echo \
		env \

SRCS = $(addprefix ${SRCDIR}, $(addsuffix .c, ${SRC}))

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

OBJS = ${SRCS:.c=.o}

#---------RULES---------#

all: 		$(NAME)

$(LIBFT):
			cd $(LIBFTDIR) && $(MAKE)

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
			@$(RM) $(OBJS) $(BONUS_OBJ)
			@cd $(LIBFTDIR) && $(MAKE) clean

fclean: 	clean
			@$(RM) $(NAME) $(BONUS) $(LIBFT)
			@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all
