# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkernbac <fkernbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 12:38:23 by rbetz             #+#    #+#              #
#    Updated: 2023/02/07 20:09:43 by fkernbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

###			###			COMPABILITY		###			###
OS		:=	$(shell uname)
BREWU	:=	/Users/$(USER)/.brewconfig.zsh

###			###			MINISHELL		###			###
CONFIG	:=	./.ms_config

###			###			COMPILER		###			###
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
CDFLAGS	:=	-g #-fsanitize=address

###			###			LIBRARIES		###			###
LIBFT_D	:=	./lib/libft/
LIB_MAC	:=	-L $(LIBFT_D) -l ft -L ~/.brew/opt/readline/lib -l readline
LIB		:=	-L $(LIBFT_D) -l ft -l readline

###			###			HEADER			###			###
INC_D	:=	./inc
INC_ALL	:=	-I $(INC_D)/ -I $(LIBFT_D)

ifeq ($(OS), Darwin)
	INC_MAC	:=	$(INC_ALL) -I ~/.brew/opt/readline/include
	CFLAGS	+=	$(INC_MAC)
else
	INC		:=	$(INC_ALL) -I /usr/include/readline
	CFLAGS	+=	$(INC)
endif

###			###			SOURCES			###			###
VPATH	:=	src/ src/builtins/ src/environment/ src/errorhandling/ src/execute/ \
			src/history/ src/memory \
			src/parsing/ src/redir/ src/signals/ src/utils/

SRC_F	:=	minishell.c
SRC_F	+=
SRC_F	+=	environment.c path.c get_set_env.c print_env.c
SRC_F	+=	errorhandling.c
SRC_F	+=	execute.c
SRC_F	+=	cleanup.c
SRC_F	+=
SRC_F	+=
SRC_F	+=	parser.c parsing_utils.c
SRC_F	+=	var_expansion.c var_utils.c remove_quotes.c quote_utils.c
SRC_F	+=	input_list.c create_cmd.c
SRC_F	+=
SRC_F	+=	cd.c echo.c env.c exit.c export.c pwd.c unset.c export_print.c
SRC_F	+=	redir.c heredoc.c infile.c outfile.c filedescriptors.c
SRC_F	+=	dup_fds.c
SRC_F	+=	signals.c
SRC_F	+=	history.c
SRC_F	+=	multijoin.c free.c skip.c ft_strcmp.c arraycount.c get_word.c
SRC_F	+=	ft_last_word.c combine_pathprog.c multijoin_array.c
SRC_F	+=	is_valid_var.c

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
all:
	@$(MAKE) $(NAME) -j

ifeq ($(OS), Darwin)
$(NAME): $(CONFIG) $(LIBFT_D)libft.a $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_F) $(LIB_MAC)
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled.$(WHITE)"
else
$(NAME): $(CONFIG) $(LIBFT_D)libft.a $(OBJ_D) $(OBJ_F)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_F) $(LIB)
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled.$(WHITE)"
endif

debug: $(LIBFT_D)libft.a $(OBJ_D) $(OBJ_F)
	$(CC) $(CDFLAGS) -o $(NAME) $(OBJ_F) $(LIB_MAC)
	@echo "$(RED)--->$(BLUE)$(NAME) is compiled in $(YELL)DEBUG$(RED)MODE!$(WHITE)"

$(OBJ_D)/%.o: %.c
	$(CC) $(CFLAGS) $(CDFLAGS) -c $< -o $@

$(OBJ_D):
	mkdir $@

%.a:
	make -j -C $(LIBFT_D)

$(CONFIG):
	@if [ ! -f "$(CONFIG)" ]; then \
		if [ "$(OS)" = "Linux" ]; then \
			apt-get install -y libreadline-dev >> /dev/null 2>&1 && touch $(CONFIG) \
		;else \
			if [ -f $(BREWU) ]; then \
				echo "check brew for readline"; \
				brew install readline >> /dev/null 2>&1 && touch $(CONFIG) \
			;else \
				curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | bash; \
				brew install readline >> /dev/null 2>&1 && touch $(CONFIG); \
			fi; \
		fi; \
	fi;

clean:
	@if [ -d "$(OBJ_D)" ]; then \
			$(RM) -rf $(OBJ_D); \
			make fclean -C $(LIBFT_D); \
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
