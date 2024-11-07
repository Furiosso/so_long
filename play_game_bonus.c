/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:58:21 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 21:35:53 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	charge_textures(t_texture *texture, t_map *map);
static void	charge_images(t_image *img, t_texture *texture, t_map *map);
static void	ft_hook(mlx_key_data_t keydata, void *param);

void	play_game(t_map *map)
{
	map->window = mlx_init(map->wide * 64, map->height * 64, "SO LONG", true);
	if (!map->window)
	{
		if (ft_printf("%s\n", (mlx_strerror(mlx_errno))) < 0)
			free_map_and_finish(map, "mlx_init");
		exit (EXIT_FAILURE);
	}
	map->texture = ft_calloc(sizeof(t_texture), 1);
	map->img = ft_calloc(sizeof(t_image), 1);
	if (!map->texture || !map->img)
		finish("malloc", 26);
	charge_textures(map->texture, map);
	charge_images(map->img, map->texture, map);
	charge_banner(map, map->texture);
	draw_image(map, map->window);
	mlx_loop_hook(map->window, &ft_close_window, map->window);
	mlx_key_hook(map->window, &ft_hook, map);
	mlx_loop_hook(map->window, &ft_animation, map);
	mlx_loop(map->window);
	clean_window(map, map->img, map->texture, map->window);
}

static void	charge_textures(t_texture *texture, t_map *map)
{
	texture->background = mlx_load_png("./textures/background.png");
	if (!texture->background)
		clean_and_exit(texture, map);
	texture->wall = mlx_load_png("./textures/muro.png");
	if (!texture->wall)
		clean_and_exit(texture, map);
	texture->player = mlx_load_png("./textures/player.png");
	if (!texture->player)
		clean_and_exit(texture, map);
	texture->collectable = mlx_load_png("./textures/collectable.png");
	if (!texture->collectable)
		clean_and_exit(texture, map);
	texture->collectable2 = mlx_load_png("./textures/collectable2.png");
	if (!texture->collectable2)
		clean_and_exit(texture, map);
	texture->exit = mlx_load_png("./textures/exit.png");
	if (!texture->exit)
		clean_and_exit(texture, map);
	texture->foe = mlx_load_png("./textures/foe2.png");
	if (!texture->foe)
		clean_and_exit(texture, map);
	texture->foe2 = mlx_load_png("./textures/foe.png");
	if (!texture->foe2)
		clean_and_exit(texture, map);
}

static void	charge_images(t_image *img, t_texture *t, t_map *map)
{
	img->background = mlx_texture_to_image(map->window, t->background);
	if (!img->background)
		clean_and_exit(t, map);
	img->wall = mlx_texture_to_image(map->window, t->wall);
	if (!img->wall)
		clean_and_exit(t, map);
	img->player = mlx_texture_to_image(map->window, t->player);
	if (!img->player)
		clean_and_exit(t, map);
	img->collectable = mlx_texture_to_image(map->window, t->collectable);
	if (!img->collectable)
		clean_and_exit(t, map);
	img->collectable2 = mlx_texture_to_image(map->window, t->collectable2);
	if (!img->collectable2)
		clean_and_exit(t, map);
	img->exit = mlx_texture_to_image(map->window, t->exit);
	if (!img->exit)
		clean_and_exit(t, map);
	img->foe = mlx_texture_to_image(map->window, t->foe);
	if (!img->foe)
		clean_and_exit(t, map);
	img->foe2 = mlx_texture_to_image(map->window, t->foe2);
	if (!img->foe2)
		clean_and_exit(t, map);
	disable_images(img->collectable2, img->foe2);
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0] - 1][map->player[1]] != '1')
		move_player(map, 1);
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0] + 1][map->player[1]] != '1')
		move_player(map, 2);
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0]][map->player[1] - 1] != '1')
		move_player(map, 3);
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0]][map->player[1] + 1] != '1')
		move_player(map, 4);
	check_enemies(map);
	check_exit(map);
}

void	call_set_items_in_window(t_map *map, int *con)
{
	set_items_in_window(map, map->texture, con);
}
