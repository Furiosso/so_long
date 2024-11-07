NAME = so_long
CC = cc
CFILES = so_long.c clean_utils.c utils.c copy_map.c manage_queue.c image_utils.c clean_window_utils.c flood_fill_utils.c
MANDATORY_FILES = flood_fill.c mandatory_utils.c movements.c play_game.c
BONUSFILES = bonus_utils.c flood_fill_bonus.c movements_bonus.c play_game_bonus.c xtra_functions_bonus.c
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address,leak
LDFLAGS = -ldl -lglfw -pthread -lm

OFILES = $(CFILES:.c=.o)
OMANDATORYFILES = $(MANDATORY_FILES:.c=.o)
OBONUSFILES = $(BONUSFILES:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = MLX42/build
MLX = $(MLX_DIR)/libmlx42.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME):$(OFILES) $(OMANDATORYFILES) $(LIBFT) $(MLX) so_long_mandatory.h
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) $(OFILES) $(OMANDATORYFILES) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

bonus:$(OFILES) $(OBONUSFILES) $(LIBFT) $(MLX) so_long_bonus.h
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) $(OFILES) $(OBONUSFILES) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)_bonus

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OFILES) $(OMANDATORYFILES) $(OBONUSFILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: all bonus clean fclean re
