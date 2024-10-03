/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:06:37 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/03 13:14:58 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	charge_textures(t_texture *texture);
void	charge_images(mlx_t *mlx, t_image *img, t_texture *texture);
void	ft_hook(mlx_key_data_t keydata, void *param);
void	ft_close_window(void *param);

int32_t	play_game(t_map *map)
{
	mlx_t		*mlx;
	t_texture	*texture;

	mlx = mlx_init((*map).wide * 64, ((*map).height - 1) * 64, "SO LONG", true);
	if (!mlx)
	{
		ft_printf("%s\n", (mlx_strerror(mlx_errno)));
		return (EXIT_FAILURE);
	}
	(*map).window = mlx;
	texture = ft_calloc(sizeof(t_texture), 1);
	(*map).img = ft_calloc(sizeof(t_image), 1);
	if (!texture || !(*map).img)
		finish("malloc", 25);
	charge_textures(texture);
	charge_images(mlx, (*map).img, texture);
	draw_image(map, mlx);
	mlx_loop_hook(mlx, &ft_close_window, mlx);
	mlx_key_hook(mlx, &ft_hook, map);
	mlx_loop(mlx);
	clean_window(map, (*map).img, texture, mlx);
	return (EXIT_SUCCESS);
}

void	charge_textures(t_texture *texture)
{
	texture->background = mlx_load_png("./temp/background.png");
	if (!texture->background)
		finish("texture", 26);
	texture->wall = mlx_load_png("./temp/muro.png");
	if (!texture->wall)
		finish("texture", 27);
	texture->player = mlx_load_png("./temp/player.png");
	if (!texture->player)
		finish("texture", 28);
	texture->collectable = mlx_load_png("./temp/collectable.png");
	if (!texture->collectable)
		finish("texture", 29);
	texture->exit = mlx_load_png("./temp/exit.png");
	if (!texture->exit)
		finish("texture", 30);
}

void	charge_images(mlx_t *mlx, t_image *img, t_texture *texture)
{
	img->background = mlx_texture_to_image(mlx, texture->background);
	if (!img->background)
		finish("image", 31);
	img->wall = mlx_texture_to_image(mlx, texture->wall);
	if (!img->wall)
		finish("image", 32);
	img->player = mlx_texture_to_image(mlx, texture->player);
	if (!img->player)
		finish("image", 33);
	img->collectable = mlx_texture_to_image(mlx, texture->collectable);
	if (!img->collectable)
		finish("image", 34);
	img->exit = mlx_texture_to_image(mlx, texture->exit);
	if (!img->exit)
		finish("image", 35);
}

void	ft_close_window(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& (*map).map[(*map).player[0] - 1][(*map).player[1]] != '1')
		move_up(map);
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& (*map).map[(*map).player[0] + 1][(*map).player[1]] != '1')
		move_down(map);
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& (*map).map[(*map).player[0]][(*map).player[1] - 1] != '1')
		move_left(map);
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& (*map).map[(*map).player[0]][(*map).player[1] + 1] != '1')
		move_right(map);
	if (((*map).player[0] == (*map).exit[0])
		&& ((*map).player[1] == (*map).exit[1]) && (*map).cs_are_found)
	{
		mlx_close_window((*map).window);
		ft_printf("Game beaten in %u movements. Kudos!!!\n", (*map).steps);
	}
}
