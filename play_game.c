/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:06:37 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/30 19:47:48 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_map(char *file, size_t *size);
void	charge_textures(t_texture *texture);
void	charge_images(mlx_t *mlx, t_image *img, t_texture *texture);

int32_t	play_game(t_map *map)
{
	mlx_t		*mlx;
	t_texture	*texture;
	t_image		*img;

	mlx = mlx_init((*map).wide * 64, ((*map).height - 1) * 64, "SO LONG", true);
	if (!mlx)
	{
		ft_printf("%s\n", (mlx_strerror(mlx_errno)));
		return (EXIT_FAILURE);
	}
	texture = ft_calloc(sizeof(t_texture), 1);
	img = ft_calloc(sizeof(t_image), 1);
	if (!texture || !img)
		finish("malloc", 40);
	charge_textures(texture);
	charge_images(mlx, img, texture);
	draw_image((*map).map, mlx, img);
	mlx_loop(mlx);
	clean_window(map, img, texture, mlx);
	return (EXIT_SUCCESS);
}

void	charge_textures(t_texture *texture)
{
	texture->background = mlx_load_png("./temp/background.png");
	if (!texture->background)
		finish("texture", 31);
	texture->wall = mlx_load_png("./temp/muro.png");
	if (!texture->wall)
		finish("texture", 32);
	texture->player = mlx_load_png("./temp/player.png");
	if (!texture->player)
		finish("texture", 33);
	texture->collectable = mlx_load_png("./temp/caca.png");
	if (!texture->collectable)
		finish("texture", 34);
	texture->exit = mlx_load_png("./temp/exit.png");
	if (!texture->exit)
		finish("texture", 35);
}

void	charge_images(mlx_t *mlx, t_image *img, t_texture *texture)
{
	img->background = mlx_texture_to_image(mlx, texture->background);
	if (!img->background)
		finish("image", 30);
	img->wall = mlx_texture_to_image(mlx, texture->wall);
	if (!img->wall)
		finish("image", 30);
	img->player = mlx_texture_to_image(mlx, texture->player);
	if (!img->player)
		finish("image", 30);
	img->collectable = mlx_texture_to_image(mlx, texture->collectable);
	if (!img->collectable)
		finish("image", 30);
	img->exit = mlx_texture_to_image(mlx, texture->exit);
	if (!img->exit)
		finish("image", 30);
}
