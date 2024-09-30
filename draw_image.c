/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:33:42 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/30 19:40:48 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_items_in_window(char **map, mlx_t *mlx, t_image *img, int *con);

void	draw_image(char **map, mlx_t *mlx, t_image *img)
{
	int	con[2];

	con[0] = 0;
	while (map[con[0]])
	{
		con[1] = 0;
		while (map[con[0]][con[1]])
		{
			if (mlx_image_to_window(mlx, img->background,
					con[1] * 64, con[0] * 64) < 0)
				finish("image_to_window", 50);
			if (map[con[0]][con[1]] != '0')
				set_items_in_window(map, mlx, img, con);
			con[1]++;
		}
		con[0]++;
	}
}

void	set_items_in_window(char **map, mlx_t *mlx, t_image *img, int *con)
{
	mlx_image_t	*temp;

	temp = NULL;
	if (map[con[0]][con[1]] == '1')
		temp = img->wall;
	if (map[con[0]][con[1]] == 'P')
		temp = img->player;
	if (map[con[0]][con[1]] == 'C')
		temp = img->collectable;
	//if (map[con[0]][con[1]] == 'E')
	//	temp = img->exit;
	if (!temp && !(map[con[0]][con[1]] == 'E'))
		finish("set_items_in_window", 70);
	if (temp)
	{
		if (mlx_image_to_window(mlx, temp, con[1] * 64, con[0] * 64) < 0)
			finish("image_to_window", 60);
	}
}
