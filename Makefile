NAME = minishell
LIBFT = libft
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/$(LIBFT)

SRC_DIR = ./src
SRC = main.c \
	parsing/dollar_handle.c \
	parsing/dollar_utils.c \
	parsing/quote_handle.c \
	parsing/token_handle.c \
	parsing/token_utils.c \
	parsing/token/token_init.c \
	parsing/token/token_clear.c \
	parsing/token/token_manage.c \
	parsing/command_check.c \
	parsing/command_fd.c \
	parsing/command_arg.c \
	parsing/command_utils.c \
	parsing/command/cmd_init.c \
	parsing/command/cmd_clear.c \
	parsing/command/cmd_manage.c \

OBJ = $(SRC:.c=.o)

SRC := $(addprefix $(SRC_DIR)/, $(SRC))

SAN = -fsanitize=address -fsanitize=leak

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./inc -I ./libft/inc 

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@${CC} ${CFLAGS} ${SAN} ${OBJ} $(LIBFT_LIB) -o $(NAME) -lreadline

$(LIBFT_LIB):
	@${MAKE} -C libft

clean:
	@${MAKE} -C libft fclean
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY : all clean fclean re
