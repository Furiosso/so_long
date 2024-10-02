/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:19:24 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/02 16:25:22 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_window(t_map *map, t_image *img, t_texture *texture, mlx_t *mlx)
{
	mlx_delete_image(mlx, img->background);
	mlx_delete_image(mlx, img->wall);
	mlx_delete_image(mlx, img->player);
	mlx_delete_image(mlx, img->collectable);
	mlx_delete_image(mlx, img->exit);
	mlx_delete_texture(texture->background);
	mlx_delete_texture(texture->wall);
	mlx_delete_texture(texture->player);
	mlx_delete_texture(texture->collectable);
	mlx_delete_texture(texture->exit);
	free(texture);
	free(img);
	clean_copy((*map).map);
	free((*map).player);
	free((*map).exit);
	free(map);
	mlx_terminate(mlx);
}
