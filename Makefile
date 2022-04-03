# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 23:35:57 by nnakarac          #+#    #+#              #
#    Updated: 2022/04/04 00:04:49 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/
LIB_DIR = libft/

INCS = -Iincludes/ -I$(LIB_DIR)includes/
NAME = server client
SRCS = server.c \
	server_utils.c \
	client.c \
	client_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	@make -C $(LIB_DIR) --silent
	$(CC) $(addprefix $(OBJ_DIR),server.o) $(addprefix $(OBJ_DIR),server_utils.o) -o server -L $(LIB_DIR) -lft
	$(CC) $(addprefix $(OBJ_DIR),client.o) $(addprefix $(OBJ_DIR),client_utils.o) -o client -L $(LIB_DIR) -lft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@

bonus: $(NAME)

clean:
	@make -C $(LIB_DIR) clean --silent
	$(RM) $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	$(RM) client
	$(RM) server

re: fclean all

test_srv:
		$(CC) server.c -o server
		./server

test_client:
	$(CC) client.c -o client
	@read -p "Enter PID: " PID \
	&& read -p "Enter FILENAME: " FD \
	&& ./client $${PID} "$$(cat $${FD})"

.PHONY:	all clean fclean re
