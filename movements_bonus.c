/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:29:30 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 16:52:03 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_collectables(t_map *map);

void	move_player(t_map *map, char move)
{
	choose_direction(map, move);
	if (!map->cs_are_found)
		check_collectables(map);
	map->steps++;
	if (ft_printf("STePs: %u\n", map->steps) < 0)
		clean_and_exit(map->texture, map, "ft_printf fail");
	charge_banner(map, map->texture);
}

static void	check_collectables(t_map *map)
{
	int32_t		coor[2];
	size_t		i;
	mlx_image_t	*collectable;

	coor[0] = map->player[0];
	coor[1] = map->player[1];
	collectable = map->img->collectable;
	if (map->map[coor[0]][coor[1]] == 'C')
	{
		map->map[coor[0]][coor[1]] = '0';
		i = -1;
		while (++i < collectable->count)
		{
			if (collectable->instances[i].y / 64 == coor[0]
				&& collectable->instances[i].x / 64 == coor[1])
			{
				collectable->instances[i].enabled = false;
				map->img->collectable2->instances[i].enabled = false;
				break ;
			}
		}
		map->collectables--;
	}
	if (!map->collectables)
		map->cs_are_found = 1;
}
