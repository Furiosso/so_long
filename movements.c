/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:46:35 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/25 11:33:08 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_collectables(t_map *map);

void	move_up(t_map *map)
{
	(*map).img->player->instances[0].y -= 64;
	(*map).player[0]--;
	if (!(*map).cs_are_found)
		check_collectables(map);
	(*map).steps++;
	ft_printf("STePs: %u\n", (*map).steps);
}

void	move_down(t_map *map)
{
	(*map).img->player->instances[0].y += 64;
	(*map).player[0]++;
	if (!(*map).cs_are_found)
		check_collectables(map);
	(*map).steps++;
	ft_printf("STePs: %u\n", (*map).steps);
}

void	move_left(t_map *map)
{
	(*map).img->player->instances[0].x -= 64;
	(*map).player[1]--;
	if (!(*map).cs_are_found)
		check_collectables(map);
	(*map).steps++;
	ft_printf("STePs: %u\n", (*map).steps);
}

void	move_right(t_map *map)
{
	(*map).img->player->instances[0].x += 64;
	(*map).player[1]++;
	if (!(*map).cs_are_found)
		check_collectables(map);
	(*map).steps++;
	ft_printf("STePs: %u\n", (*map).steps);
}

static void	check_collectables(t_map *map)
{
	int32_t		y;
	int32_t		x;
	size_t		i;
	mlx_image_t	*collectable;

	y = (*map).player[0];
	x = (*map).player[1];
	collectable = (*map).img->collectable;
	if ((*map).map[y][x] == 'C')
	{
		(*map).map[y][x] = '0';
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
		(*map).collectables--;
	}
	if (!(*map).collectables)
		(*map).cs_are_found = 1;
}
