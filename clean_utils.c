/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:19:24 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 19:16:01 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_line_and_exit(char *line, int fd, const char *s)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 6);
	end(s, 11);
}

void	free_map_and_exit(t_map *map, const char *s, char **copy)
{
	if (copy)
		clean_copy(copy);
	if (map->map)
		clean_copy(map->map);
	if (map->player)
		free(map->player);
	free(map);
	end(s, 7);
}

void	free_map_and_finish(t_map *map, const char *s)
{
	if (map->map)
		free(map->map);
	if (map->player)
		free(map->player);
	free(map);
	finish(s, 8);
}

void	check_exit(t_map *map)
{
	if ((map->map[map->player[0]][map->player[1]] == 'E') && map->cs_are_found)
	{
		mlx_close_window(map->window);
		if (ft_printf("Total movements: %u. Kudos!!!\n", map->steps) < 0)
			clean_and_exit(map->texture, map, "ft_printf fail");
	}
}
