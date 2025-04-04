# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 10:29:28 by sabdulba          #+#    #+#              #
#    Updated: 2025/03/07 12:29:33 by sabdulba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	$(wildcard *.c src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c)

RM = rm -rf

CFLAGS = -Werror -Wall -Wextra

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = gcc -g -pthread #-fsanitize=address 

NONE='\033[0m'
GREEN='\033[32m'
RED='\033[31m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
WARNING='\033[33m'

all: $(NAME)

$(NAME): $(SRC) $(OBJS)
	@$(CC) $(OBJS) -o $@
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ_DIR)/%.o: %.c
	@echo $(CURSIVE)$(GRAY) "     - Building $<" $(NONE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(OBJ_DIR)
	@echo $(CURSIVE)$(RED) "     - Object files removed" $(NONE)

fclean: clean
	@rm -f $(NAME)
	@echo $(CURSIVE)$(RED) "     - $(NAME) removed" $(NONE)

re: fclean all

.PHONY: all clean fclean re