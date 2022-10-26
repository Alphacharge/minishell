# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 12:38:23 by rbetz             #+#    #+#              #
#    Updated: 2022/10/26 16:23:07 by rbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAIN_F = main.c
SHAR_F = 

SRC_D = ./src
OBJ_D = ./obj
MAIN_O = $(addprefix $(OBJ_D)/, $(MAIN_F:%.c=%.o))
SHAR_O = $(addprefix $(OBJ_D)/, $(SHAR_F:%.c=%.o))

INC_F = $(INC_D)/$(NAME).h
INC_D = ./inc

CC = cc
CFLAGS = -Wall -Wextra -Werror
CDFLAGS = #-g -fsanitize=address

RED = \033[1;31m
GREEN = \033[1;32m
YELL = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[0m

all: $(NAME)

$(NAME): $(OBJ_D) $(SHAR_O) $(MAIN_O)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_O) $(SHAR_O)
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled.$(WHITE)"

debug: clean $(OBJ_D) $(SHAR_O) $(MAIN_O)
	$(CC) $(CDFLAGS) -o $(NAME) $(MAIN_O) $(SHAR_O)
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled in $(RED)DEBUG$(YELL)MODE.$(WHITE)"
	
$(OBJ_D)/%.o: $(SRC_D)/%.c $(INC_F)
	$(CC) $(CFLAGS) $(CDFLAGS) -I $(INC_D) -c $< -o $@

$(OBJ_D):
	mkdir $@

clean:
	@if [ -d "$(OBJ_D)" ]; then \
			$(RM) -rf $(OBJ_D); \
			echo "$(RED)Cleaning Objects:\n $(WHITE)$(MAIN_O) $(SHAR_O)";else \
			echo "$(GREEN)No Objects to remove.$(WHITE)"; \
	fi;

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			$(RM) -f $(NAME); \
			echo "$(YELL)Cleaning Exec:\n$(WHITE)$(NAME)";else \
			echo "No $(NAME) to remove."; \
	fi;

re: fclean all

.PHONY: all clean fclean re bonus debug