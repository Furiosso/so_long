/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:13:17 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/03 21:17:01 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	set_items_in_window(char **map, mlx_t *mlx, t_image *img, int *con);

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
				finish("image_to_window", 27);
			if (map[con[0]][con[1]] != '0'
				&& map[con[0]][con[1]] != 'P')
				set_items_in_window(map, mlx, img, con);
		}
	}
	playr = source->player;
	if (mlx_image_to_window(mlx, img->player, playr[1] * 64, playr[0] * 64) < 0)
		finish("image_to_window", 30);
}

static void	set_items_in_window(char **map, mlx_t *mlx, t_image *img, int *con)
{
	mlx_image_t	*temp;

	temp = NULL;
	if (map[con[0]][con[1]] == '1')
		temp = img->wall;
	if (map[con[0]][con[1]] == 'C')
		temp = img->collectable;
	if (map[con[0]][con[1]] == 'E')
		temp = img->exit;
	if (map[con[0]][con[1]] == 'F')
		temp = img->foe;
	if (!temp)
		finish("set_items_in_window", 28);
	if (temp)
	{
		if (mlx_image_to_window(mlx, temp, con[1] * 64, con[0] * 64) < 0)
			finish("image_to_window", 29);
	}
}

void	check_name(char *name)
{
	char	*needle;
	char	*ber;

	needle = ft_strrchr(name, '/');
	if (!needle)
		return ;
	ber = ".ber";
	needle++;
	while (*needle && *ber)
	{
		if (*needle != *ber)
			return ;
		needle++;
		ber++;
	}
	end ("Nameless document", 31);
}
