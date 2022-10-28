NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra

GNLSRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNLOBJ = $(GNLSRC:.c=.o)

PRINTFSRC = ft_printf/ft_printf.c ft_printf/ft_hexa_conv.c ft_printf/ft_hexa_ptr.c ft_printf/ft_itoa_count.c ft_printf/ft_u_itoa_count.c
PRINTFOBJ = $(PRINTFSRC:.c=.o)

LIBFTSRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_strstr.c
LIBFTOBJ = $(LIBFTSRC:.c=.o)

RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELL	=	\033[1;33m
BLUE	=	\033[1;34m
WHITE	=	\033[0m

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFTOBJ) $(PRINTFOBJ) $(GNLOBJ)
	ar rcs $(NAME) $(LIBFTOBJ) $(PRINTFOBJ) $(GNLOBJ)

clean:
	@echo "$(RED)Cleaning Objects:\n$(WHITE)$(LIBFTOBJ) $(PRINTFOBJ) $(GNLOBJ)"
	@/bin/rm -f $(LIBFTOBJ) $(PRINTFOBJ) $(GNLOBJ) libft.h.gch

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		/bin/rm -f $(NAME); \
		echo "$(YELL)Cleaning Lib:\n$(WHITE)$(NAME)";else \
		echo "No $(NAME) to remove."; \
	fi;

re: fclean all
