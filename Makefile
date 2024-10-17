NAME = so_long
CC = cc
CFILES = so_long.c utils.c flood_fill.c copy_map.c manage_queue.c play_game.c clean_utils.c draw_image.c movements.c
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address,leak -g3
LFLAGS = -ldl -lglfw -pthread -lm

OFILES = $(CFILES:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = MLX42/build
MLX = $(MLX_DIR)/libmlx42.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME):$(OFILES) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) $(OFILES) $(LIBFT) $(MLX) $(LFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OFILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
