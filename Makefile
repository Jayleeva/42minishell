NAME = minishell
LIBFT = libft
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/$(LIBFT)

SRC_DIR = ./src
SRC = main.c
OBJ = $(SRC:.c=.o)

SRC := $(addprefix $(SRC_DIR)/, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./inc -I ./libft/inc -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@${CC} ${CFLAGS} ${OBJ} $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	@${MAKE} -C libft

clean:
	@${MAKE} -C libft fclean
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY : all clean fclean re