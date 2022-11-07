# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 12:38:23 by rbetz             #+#    #+#              #
#    Updated: 2022/11/07 21:04:58 by fkernbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

###			###			COMPILER		###			###
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
CDFLAGS	:=	#-g -fsanitize=address

###			###			LIBRARYS		###			###
LIBFT_D	:=	./lib/libft/
LIB		:=	-L $(LIBFT_D) -l ft -L ~/.brew/opt/readline -l readline

###			###			HEADER			###			###
INC_D	:=	./inc
INC		:=	-I $(INC_D)/ -I $(LIBFT_D)
CFLAGS	+=	$(INC)

###			###			SOURCES			###			###
VPATH	:=	src/ src/builtins/ src/environment/ src/errorhandling/ src/execute/ \
			src/filedescriptors/ src/filedescriptors/ src/history/ src/parsing/ \
			src/pipes/ src/redirects/ src/signal/ src/utils/

SRC_F	:=	minishell.c
SRC_F	+=
SRC_F	+=	get_env.c
SRC_F	+=	clean.c errorhandling.c
SRC_F	+=	execute.c
SRC_F	+=	check_infile.c check_outfile.c close.c
SRC_F	+=
SRC_F	+=	parse_args.c parse_progs.c
SRC_F	+=
SRC_F	+=	combine_pathprog.c first_word.c multijoin.c
SRC_F	+=	ft_free.c

###			###			OBJECTS			###			###
OBJ_D	:=	./obj
OBJ_F	:=	$(patsubst %.c,$(OBJ_D)/%.o,$(SRC_F))

###			###			COLORS			###			###
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELL	=	\033[1;33m
BLUE	=	\033[1;34m
WHITE	=	\033[0m

###			###			RULES			###			###
all: $(NAME)

$(NAME): $(LIBFT_D)libft.a $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_F) $(LIB)
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled.$(WHITE)"

$(OBJ_D)/%.o: %.c
	@$(CC) $(CFLAGS) $(CDFLAGS) -c $< -o $@

$(OBJ_D):
	mkdir $@

%.a:
	make -C $(LIBFT_D)

clean:
	@if [ -d "$(OBJ_D)" ]; then \
			$(RM) -rf $(OBJ_D); \
			echo "$(RED)Cleaning Objects:\n $(WHITE)$(OBJ_F)";else \
			echo "$(GREEN)No Objects to remove.$(WHITE)"; \
	fi;

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			$(RM) -f $(NAME); \
			echo "$(YELL)Cleaning Exec:\n$(WHITE)$(NAME)";else \
			echo "No $(NAME) to remove."; \
	fi;

re: fclean all

.PHONY: all clean fclean re
