/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:33:42 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/02 18:24:15 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_items_in_window(char **map, mlx_t *mlx, t_image *img, int *con);

void	draw_image(t_map *source, mlx_t *mlx)
{
	int		con[2];
	t_image	*img;
	char	**map;
	int32_t	*playr;

	img = (*source).img;
	map = (*source).map;
	con[0] = -1;
	while (map[++con[0]])
	{
		con[1] = -1;
		while (map[con[0]][++con[1]])
		{
			if (mlx_image_to_window(mlx, img->background,
					con[1] * 64, con[0] * 64) < 0)
				finish("image_to_window", 36);
			if (map[con[0]][con[1]] != '0'
				&& map[con[0]][con[1]] != 'P')
				set_items_in_window(map, mlx, img, con);
		}
	}
	playr = (*source).player;
	if (mlx_image_to_window(mlx, img->player, playr[1] * 64, playr[0] * 64) < 0)
		finish("image_to_window", 37);
}

void	set_items_in_window(char **map, mlx_t *mlx, t_image *img, int *con)
{
	mlx_image_t	*temp;

	temp = NULL;
	if (map[con[0]][con[1]] == '1')
		temp = img->wall;
	if (map[con[0]][con[1]] == 'C')
		temp = img->collectable;
	if (map[con[0]][con[1]] == 'E')
		temp = img->exit;
	if (!temp)
		finish("set_items_in_window", 38);
	if (temp)
	{
		if (mlx_image_to_window(mlx, temp, con[1] * 64, con[0] * 64) < 0)
			finish("image_to_window", 39);
	}
}
