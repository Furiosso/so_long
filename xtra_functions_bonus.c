/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtra_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:43:04 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 19:07:08 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_enemies(t_map *map)
{
	if (map->map[map->player[0]][map->player[1]] == 'F')
	{
		mlx_close_window(map->window);
		if (ft_printf("YOU LOST!!!\n") < 0)
			clean_and_exit(map->texture, map, "ft_printf fail");
	}
}

void	charge_banner(t_map *map, t_texture *texture)
{
	char	*steps;

	if (map->counter)
		mlx_delete_image(map->window, map->counter);
	steps = ft_itoa(map->steps);
	if (!steps)
		clean_and_exit(texture, map, "ft_itoa fail");
	map->counter = mlx_put_string(map->window, steps,
			map->wide * 32 - 24, map->height * 64 - 40);
	free(steps);
	if (!map->counter)
		clean_and_exit(texture, map, mlx_strerror(mlx_errno));
}

void	disable_images(mlx_image_t *collectable, mlx_image_t *foe)
{
	collectable->enabled = false;
	foe->enabled = false;
}

void	ft_animation(void *param)
{
	t_map		*map;
	static int	i = 0;

	map = param;
	i++;
	if (i == 30)
	{
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

void	put_to_win(t_map *map, mlx_image_t *temp, int *con, t_texture *t)
{
	if (mlx_image_to_window(map->window, temp, con[1] * 64, con[0] * 64) < 0)
		clean_and_exit(t, map, mlx_strerror(mlx_errno));
}
