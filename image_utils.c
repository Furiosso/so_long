/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:11:14 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 19:27:16 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image(t_map *source, mlx_t *mlx)
{
	int		con[2];
	t_image	*img;
	char	**map;
	int32_t	*playr;

	img = source->img;
	map = source->map;
	con[0] = -1;
	while (map[++con[0]])
	{
		con[1] = -1;
		while (map[con[0]][++con[1]])
		{
			if (mlx_image_to_window(mlx, img->background,
					con[1] * 64, con[0] * 64) < 0)
				clean_and_exit(source->texture, source,
					mlx_strerror(mlx_errno));
			if (map[con[0]][con[1]] != '0'
				&& map[con[0]][con[1]] != 'P')
				call_set_items_in_window(source, con);
		}
	}
	playr = source->player;
	if (mlx_image_to_window(mlx, img->player, playr[1] * 64, playr[0] * 64) < 0)
		clean_and_exit(source->texture, source, mlx_strerror(mlx_errno));
}

void	choose_direction(t_map *map, char move)
{
	if (move == 1)
	{
		map->img->player->instances[0].y -= 64;
		map->player[0]--;
	}
	if (move == 2)
	{
		map->img->player->instances[0].y += 64;
		map->player[0]++;
	}
	if (move == 3)
	{
		map->img->player->instances[0].x -= 64;
		map->player[1]--;
	}
	if (move == 4)
	{
		map->img->player->instances[0].x += 64;
		map->player[1]++;
	}
}

void	clean_and_exit(t_texture *texture, t_map *map, const char *s)
{
	clean_window(map, map->img, texture, map->window);
	end(s, 20);
}

void	ft_close_window(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	copy_line(t_map *map, char **copy, size_t con)
{
	map->map[con] = ft_strdup(copy[con]);
	if (!map->map[con])
		free_map_and_exit(map, "ft_strdup", copy);
}
