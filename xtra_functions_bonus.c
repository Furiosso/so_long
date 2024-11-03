/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtra_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:43:04 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/03 21:13:44 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_enemies(t_map *map)
{
	if (map->map[map->player[0]][map->player[1]] == 'F')
	{
		mlx_close_window(map->window);
		ft_printf("YOU LOST!!!\n");
	}
}

void	charge_banner(t_map *map)
{
	/*mlx_image_t	*banner;

	banner = mlx_new_image(mlx, width * 64, 64);
	if (!banner)
		finish("mlx_new_image", 34);
    ft_memset(banner->pixels, 227, width * 64 * 64 * sizeof(int32_t));
    if (mlx_image_to_window(mlx, banner, 0, height * 64 - 64) < 0)
		finish("mlx_image_to_window", 35);*/
	if (map->counter)
		mlx_delete_image(map->window, map->counter);
	map->counter = mlx_put_string(map->window, ft_itoa(map->steps),
			map->wide * 32 - 24, map->height * 64 - 40);
	if (!map->counter)
		finish("mlx_put_string", 35);
}

void	disable_images(mlx_image_t *collectable, mlx_image_t *foe)
{
	collectable->enabled = false;
	foe->enabled = false;
}

void	ft_animation(void *param)
{
	t_map	*map;
	int	i;

	map = param;
	i = 0;
	while (++i < 361)
	{
		if (i < 360)
			continue ;
		if (map->img->collectable->enabled == true)
		{
			map->img->collectable->enabled = false;
			map->img->collectable2->enabled = true;
			map->img->foe->enabled = false;
			map->img->foe2->enabled = true;
		}
		else
		{
			map->img->collectable->enabled = true;
			map->img->collectable2->enabled = false;
			map->img->foe->enabled = true;
			map->img->foe2->enabled = false;
		}
		i = 0;
	}
}