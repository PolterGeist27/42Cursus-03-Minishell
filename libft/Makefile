# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 08:46:18 by pealexan          #+#    #+#              #
#    Updated: 2023/04/30 16:15:47 by pealexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

#----------DIRS----------#
DIR = ./srcs/

SRCS =	ft_abs.c \
	ft_atoi.c \
	ft_atol.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_free_split.c \
	ft_getlength.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isnumeric.c \
	ft_isprint.c \
	ft_isquote.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_max.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_min.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_utoa.c \
	ft_wordcount.c \
	get_next_line.c \
	get_next_line_multifd.c \
	ft_printf/ft_format_lowerhexa.c \
	ft_printf/ft_format_putaddress2.c \
	ft_printf/ft_format_putaddress.c \
	ft_printf/ft_format_putchar.c \
	ft_printf/ft_format_putnbr.c \
	ft_printf/ft_format_putposnbr.c \
	ft_printf/ft_format_putstr.c \
	ft_printf/ft_format_putunsignnbr.c \
	ft_printf/ft_format_upperhexa.c \
	ft_printf/ft_get_format.c \
	ft_printf/ft_get_hexastr.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_putaddress.c \
	ft_printf/ft_putchar.c \
	ft_printf/ft_puthexa.c \
	ft_printf/ft_putnbr.c \
	ft_printf/ft_putstr.c \
	ft_printf/ft_putunsignednbr.c \

SRC = $(addprefix ${DIR}, ${SRCS})

#--------COMMANDS--------#
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

YELLOW	=	\033[0;33m

#---------RULES---------#
.c.o:
		@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: 		$(NAME)
		@echo "$(YELLOW)[Compiled libft]"

$(NAME): 	$(OBJ)
		@$(AR) $(NAME) $(OBJ)

clean:
		@$(RM) $(OBJ)

fclean: 	clean
		@$(RM) $(NAME)

re: 		fclean all
