NAME     = computor
SRC      = computor.c
OBJ      = $(SRC:.c=.o)
LIBFT    = libft/libft.a

CC       = cc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -Ilibft/inc
LDFLAGS  = -Llibft -lft -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
