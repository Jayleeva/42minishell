NAME = minishell
LIBFT = libft
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/$(LIBFT)

SRC_DIR = ./src
SRC = main.c \
	parsing/utils.c \
	parsing/dollar_handle.c \
	parsing/dollar_utils.c \
	parsing/quote_handle.c \
	parsing/token_handle.c \
	parsing/token/token_init.c \
	parsing/token/token_clear.c \
	parsing/token/token_manage.c \

OBJ = $(SRC:.c=.o)

SRC := $(addprefix $(SRC_DIR)/, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -I ./inc -I ./libft/inc 

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@${CC} ${CFLAGS} ${OBJ} $(LIBFT_LIB) -o $(NAME) -lreadline

$(LIBFT_LIB):
	@${MAKE} -C libft

clean:
	@${MAKE} -C libft fclean
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY : all clean fclean re
