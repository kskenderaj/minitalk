# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kskender <kskender@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/28 15:13:13 by kskender          #+#    #+#              #
#    Updated: 2025/07/20 16:41:29 by kskender         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCD = src
OBJD = obj
LIBFT = include/reallibft/libft.a
PRINTF = include/realf/libftprintf.a

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

# Source files
CLIENT_SRC = $(SRCD)/client.c
SERVER_SRC = $(SRCD)/server.c

# Object files
CLIENT_OBJ = $(OBJD)/client.o
SERVER_OBJ = $(OBJD)/server.o

all: $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	@make -C include/reallibft

$(PRINTF):
	@make -C include/realf

$(OBJD):
	@mkdir -p $(OBJD)

$(CLIENT_OBJ): $(SRCD)/client.c | $(OBJD)
	@printf "$(YELLOW)Compiling client...$(NC)\n"
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(SERVER_OBJ): $(SRCD)/server.c | $(OBJD)
	@printf "$(YELLOW)Compiling server...$(NC)\n"
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(NAME_CLIENT): $(CLIENT_OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $< -Linclude/reallibft -Linclude/realf -lft -lftprintf -o $@
	@printf "$(GREEN)Client built!$(NC)\n"

$(NAME_SERVER): $(SERVER_OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $< -Linclude/reallibft -Linclude/realf -lft -lftprintf -o $@
	@printf "$(GREEN)Server built!$(NC)\n"

clean:
	@printf "$(RED)Cleaning...$(NC)\n"
	@rm -rf $(OBJD)
	@make -C include/reallibft clean
	@make -C include/realf clean

fclean: clean
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@make -C include/reallibft fclean
	@make -C include/realf fclean

re: fclean all

.PHONY: all clean fclean re