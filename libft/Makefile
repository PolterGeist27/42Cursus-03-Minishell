DIRPRINT = ./srcs/printf/

DIRGNL = ./srcs/get_next_line/

DIRINCS = ./includes/

DIRLIB = ./srcs/libft/

SRC =	ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strlcpy \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_strdup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_striteri \
		ft_strmapi \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_lstnew \
		ft_lstadd_front \
		ft_lstsize \
		ft_lstlast \
		ft_lstadd_back \
		ft_lstdelone \
		ft_lstclear \
		ft_lstiter \
		ft_lstmap \

GNL =	get_next_line_bonus

PRINT = ft_printf \
		token_utils \
		print_c \
		print_i \
		printf_utils \
		print_u \
		print_percent \
		print_s \
		print_p \
		print_x \

SRCS =	$(addprefix ${DIRLIB}, $(addsuffix .c, ${SRC}))		\
		$(addprefix ${DIRGNL}, $(addsuffix .c, ${GNL}))		\
		$(addprefix ${DIRPRINT}, $(addsuffix .c, ${PRINT}))	\

OBJS = $(SRCS:.c=.o)

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I $(DIRINCS)
CC = cc
LIBC = ar rc
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

bonus: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
