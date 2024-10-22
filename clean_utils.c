/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:19:24 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/22 13:57:18 by dagimeno         ###   ########.fr       */
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
	clean_copy(map->map);
	free(map->player);
	free(map->exit);
	free(map);
	mlx_terminate(mlx);
}

void	free_line_and_exit(char *line, int fd, char *s)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 5);
	end(s, 10);
}

void	free_map_and_exit(t_map *map, char *s, char **copy)
{
	if (copy)
		clean_copy(copy);
	if (map->map)
		clean_copy(map->map);
	if (map->player)
		free(map->player);
	if (map->exit)
		free(map->exit);
	free(map);
	end(s, 11);
}

void	free_map_and_finish(t_map *map, char *s)
{
	if (map->map)
		free(map->map);
	if (map->player)
		free(map->player);
	if (map->exit)
		free(map->exit);
	free(map);
	finish(s, 12);
}

void	get_width_and_height(int32_t *width, int32_t *height)
{
	mlx_t	*mlx;

	mlx = mlx_init(1, 1, "temporal", false);
	if (!mlx)
	{
		ft_printf("%s\n", (mlx_strerror(mlx_errno)));
		exit (EXIT_FAILURE);
	}
	mlx_get_monitor_size(0, width, height);
	mlx_terminate(mlx);
}
