/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:46:35 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 16:52:23 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_mandatory.h"

static void	check_collectables(t_map *map);

void	move_player(t_map *map, char move)
{
	choose_direction(map, move);
	if (!map->cs_are_found)
		check_collectables(map);
	map->steps++;
	if (ft_printf("STePs: %u\n", map->steps) < 0)
		clean_and_exit(map->texture, map, "ft_printf fail");
}

static void	check_collectables(t_map *map)
{
	int32_t		y;
	int32_t		x;
	size_t		i;
	mlx_image_t	*collectable;

	y = map->player[0];
	x = map->player[1];
	collectable = map->img->collectable;
	if (map->map[y][x] == 'C')
	{
		map->map[y][x] = '0';
		i = -1;
		while (++i < collectable->count)
		{
			if (collectable->instances[i].y / 64 == y
				&& collectable->instances[i].x / 64 == x)
			{
				collectable->instances[i].enabled = false;
				break ;
			}
		}
		map->collectables--;
	}
	if (!map->collectables)
		map->cs_are_found = 1;
}
