# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbetz <rbetz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 12:38:23 by rbetz             #+#    #+#              #
#    Updated: 2022/10/26 17:34:58 by rbetz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAIN_F = main.c
BUIL_F = 
ENVI_F = 
ERRO_F = 
HIST_F = 
PARS_F = 
PIPE_F = 
REDI_F = 
SIGN_F = 

SRC_D = ./src
BUIL_D = /builtins/
ENVI_D = /environment/
ERRO_D = /errorhandling/
HIST_D = /history/
PARS_D = /parsing/
PIPE_D = /pipes/
REDI_D = /redirects/
SIGN_D = /signals/
OBJ_D = ./obj
MAIN_O = $(addprefix $(OBJ_D)/, $(MAIN_F:%.c=%.o))
BUIL_O = $(addprefix $(OBJ_D)/, $(BUIL_F:%.c=%.o))
ENVI_O = $(addprefix $(OBJ_D)/, $(ENVI_F:%.c=%.o))
ERRO_O = $(addprefix $(OBJ_D)/, $(ERRO_F:%.c=%.o))
HIST_O = $(addprefix $(OBJ_D)/, $(HIST_F:%.c=%.o))
PARS_O = $(addprefix $(OBJ_D)/, $(PARS_F:%.c=%.o))
PIPE_O = $(addprefix $(OBJ_D)/, $(PIPE_F:%.c=%.o))
REDI_O = $(addprefix $(OBJ_D)/, $(REDI_F:%.c=%.o))
SIGN_O = $(addprefix $(OBJ_D)/, $(SIGN_F:%.c=%.o))

INC_F = $(INC_D)/$(NAME).h
INC_D = ./inc
HEADER_F = -I $(LIBFT_D) -I $(SRC_D)$(BUIL_D) -I $(SRC_D)$(ENVI_D) -I $(SRC_D)$(ERRO_D) \
			-I $(SRC_D)$(HIST_D) -I $(SRC_D)$(PARS_D) -I $(SRC_D)$(PIPE_D) -I $(SRC_D)$(REDI_D) -I $(SRC_D)$(SIGN_D)

LIBFT= $(LIBFT_D)libft.a
LIBFT_D= ./lib/libft/

CC = cc
CFLAGS = -Wall -Wextra -Werror
CDFLAGS = #-g -fsanitize=address

RED = \033[1;31m
GREEN = \033[1;32m
YELL = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_D) $(BUIL_O) $(ENVI_O) $(ERRO_O) $(HIST_O) $(PARS_O) $(PIPE_O) $(REDI_O) $(SIGN_O) $(MAIN_O)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_O) $(BUIL_O) $(ENVI_O) $(ERRO_O) $(HIST_O) $(PARS_O) $(PIPE_O) $(REDI_O) $(SIGN_O) -L $(LIBFT_D) -l ft
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled.$(WHITE)"

debug: clean $(LIBFT) $(OBJ_D) $(BUIL_O) $(ENVI_O) $(ERRO_O) $(HIST_O) $(PARS_O) $(PIPE_O) $(REDI_O) $(SIGN_O) $(MAIN_O)
	$(CC) $(CDFLAGS) -o $(NAME) $(MAIN_O) $(BUIL_O) $(ENVI_O) $(ERRO_O) $(HIST_O) $(PARS_O) $(PIPE_O) $(REDI_O) $(SIGN_O) -L $(LIBFT_D) -l ft
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled in $(RED)DEBUG$(YELL)MODE.$(WHITE)"
	
$(OBJ_D)/%.o: $(SRC_D)/%.c $(INC_F)
	$(CC) $(CFLAGS) $(CDFLAGS) -I $(INC_D) $(HEADER_F) -c $< -o $@

$(OBJ_D):
	mkdir $@

$(LIBFT):
	make -C $(LIBFT_D)
	
clean:
	@if [ -d "$(OBJ_D)" ]; then \
			$(RM) -rf $(OBJ_D); \
			make fclean -C $(LIBFT_D); \
			echo "$(RED)Cleaning Objects:\n $(WHITE)$(MAIN_O) $(BUIL_O) $(ENVI_O) $(ERRO_O) $(HIST_O) $(PARS_O) $(PIPE_O) $(REDI_O) $(SIGN_O)";else \
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