NAME = so_long
CC = cc
CFILES = so_long.c utils.c flood_fill.c copy_map.c manage_queue.c
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,leak -g3

OFILES = $(CFILES:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME):$(OFILES) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) $(OFILES) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OFILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
