NAME = libftprintf.a
SRCS = ft_printf.c ft_print_utils.c ft_number_utils.c \


OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean	
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re