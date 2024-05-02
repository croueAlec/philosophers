# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acroue <acroue@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 11:51:52 by acroue            #+#    #+#              #
#    Updated: 2024/05/02 14:05:59 by acroue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = philosophers

# Colors
DEFAULT    = \033[0m
BLACK    = \033[0;30m
RED        = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
BWHITE    = \033[1;37m

# Directories
OBJS_DIR = objs

# Files

define SRC :=
	main.c
	mutex_handling.c
	mutex_init.c
	philo_init.c
	philo_utils.c
	routine_utils.c
	routine.c
endef
SRC := $(strip $(SRC))

OBJ := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
LIB_FLAGS = --no-print-directory --silent

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJS_DIR)/%.o: %.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)/
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)! Removing$(DEFAULT) ${OBJS_DIR} files"
	@${RM} ${OBJS_DIR}

fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

re: fclean all

cre:
	@clear
	@make re --no-print-directory

norm:
	@norminette | awk '/'Error'/ {print; found=1} END {if (!found) print "$(PURPLE)Norm O.K.$(DEFAULT)"}'
