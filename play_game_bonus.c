/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:58:21 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/03 21:15:13 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	charge_textures(t_texture *texture);
static void	charge_images(mlx_t *mlx, t_image *img, t_texture *texture);
static void	ft_hook(mlx_key_data_t keydata, void *param);
static void	ft_close_window(void *param);

int32_t	play_game(t_map *map)
{
	mlx_t		*mlx;
	t_texture	*texture;

	mlx = mlx_init(map->wide * 64, map->height * 64, "SO LONG", true);
	if (!mlx)
	{
		ft_printf("%s\n", (mlx_strerror(mlx_errno)));
		return (EXIT_FAILURE);
	}
	map->window = mlx;
	texture = ft_calloc(sizeof(t_texture), 1);
	map->img = ft_calloc(sizeof(t_image), 1);
	if (!texture || !map->img)
		finish("malloc", 16);
	charge_textures(texture);
	charge_images(mlx, map->img, texture);
	charge_banner(map);
	draw_image(map, mlx);
	mlx_loop_hook(mlx, &ft_close_window, mlx);
	//mlx_loop_hook(mlx, &ft_animation, map);
	mlx_key_hook(mlx, &ft_hook, map);
	mlx_loop(mlx);
	clean_window(map, map->img, texture, mlx);
	return (EXIT_SUCCESS);
}

static void	charge_textures(t_texture *texture)
{
	texture->background = mlx_load_png("./textures/background.png");
	if (!texture->background)
		finish("texture", 17);
	texture->wall = mlx_load_png("./textures/muro.png");
	if (!texture->wall)
		finish("texture", 18);
	texture->player = mlx_load_png("./textures/player.png");
	if (!texture->player)
		finish("texture", 19);
	texture->collectable = mlx_load_png("./textures/collectable.png");
	if (!texture->collectable)
		finish("texture", 20);
	texture->collectable2 = mlx_load_png("./textures/collectable2.png");
	if (!texture->collectable2)
		finish("texture", 38);
	texture->exit = mlx_load_png("./textures/exit.png");
	if (!texture->exit)
		finish("texture", 21);
	texture->foe = mlx_load_png("./textures/foe.png");
	if (!texture->foe)
		finish("texture", 32);
	texture->foe2 = mlx_load_png("./textures/foe2.png");
	if (!texture->foe2)
		finish("texture", 37);
}

static void	charge_images(mlx_t *mlx, t_image *img, t_texture *texture)
{
	img->background = mlx_texture_to_image(mlx, texture->background);
	if (!img->background)
		finish("image", 22);
	img->wall = mlx_texture_to_image(mlx, texture->wall);
	if (!img->wall)
		finish("image", 23);
	img->player = mlx_texture_to_image(mlx, texture->player);
	if (!img->player)
		finish("image", 24);
	img->collectable = mlx_texture_to_image(mlx, texture->collectable);
	if (!img->collectable)
		finish("image", 25);
	img->collectable2 = mlx_texture_to_image(mlx, texture->collectable2);
	if (!img->collectable2)
		finish("image", 39);
	img->exit = mlx_texture_to_image(mlx, texture->exit);
	if (!img->exit)
		finish("image", 26);
	img->foe = mlx_texture_to_image(mlx, texture->foe);
	if (!img->foe)
		finish("image", 33);
	img->foe2 = mlx_texture_to_image(mlx, texture->foe2);
	if (!img->foe2)
		finish("image", 40);
	disable_images(img->collectable2, img->foe2);
}

static void	ft_close_window(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0] - 1][map->player[1]] != '1')
		move_up(map);
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0] + 1][map->player[1]] != '1')
		move_down(map);
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0]][map->player[1] - 1] != '1')
		move_left(map);
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& map->map[map->player[0]][map->player[1] + 1] != '1')
		move_right(map);
	check_enemies(map);
	if ((map->map[map->player[0]][map->player[1]] == 'E') && map->cs_are_found)
	{
		mlx_close_window(map->window);
		ft_printf("Game beaten in %u movements. Kudos!!!\n", map->steps);
	}
}
