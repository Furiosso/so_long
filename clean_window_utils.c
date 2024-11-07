/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_window_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:33:02 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 14:01:41 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	delete_images(mlx_t *mlx, t_image *img, t_map *map);
static void	delete_textures(t_texture *texture);

void	clean_window(t_map *map, t_image *img, t_texture *texture, mlx_t *mlx)
{
	delete_images(mlx, img, map);
	delete_textures(texture);
	free(texture);
	free(img);
	clean_copy(map->map);
	free(map->player);
	free(map);
	mlx_terminate(mlx);
}

static void	delete_images(mlx_t *mlx, t_image *img, t_map *map)
{
	if (img->background)
		mlx_delete_image(mlx, img->background);
	if (img->wall)
		mlx_delete_image(mlx, img->wall);
	if (img->player)
		mlx_delete_image(mlx, img->player);
	if (img->collectable)
		mlx_delete_image(mlx, img->collectable);
	if (img->collectable2)
		mlx_delete_image(mlx, img->collectable2);
	if (img->exit)
		mlx_delete_image(mlx, img->exit);
	if (img->foe)
		mlx_delete_image(mlx, img->foe);
	if (img->foe2)
		mlx_delete_image(mlx, img->foe2);
	if (map->counter)
		mlx_delete_image(mlx, map->counter);
}

static void	delete_textures(t_texture *texture)
{
	if (texture->background)
		mlx_delete_texture(texture->background);
	if (texture->wall)
		mlx_delete_texture(texture->wall);
	if (texture->player)
		mlx_delete_texture(texture->player);
	if (texture->collectable)
		mlx_delete_texture(texture->collectable);
	if (texture->collectable2)
		mlx_delete_texture(texture->collectable2);
	if (texture->exit)
		mlx_delete_texture(texture->exit);
	if (texture->foe)
		mlx_delete_texture(texture->foe);
	if (texture->foe2)
		mlx_delete_texture(texture->foe2);
}
