/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:36:01 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/28 17:49:33 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_mandatory.h"

void	check_map(char *map)
{
	int		fd;
	int32_t	len[4];
	char	wall;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		finish(map, 21);
	line = check_first_line(fd);
	get_width_and_height(&len[2], &len[3]);
	len[0] = ft_strlen(line) - 1;
	check_size(len[0] * 64, len[2], line, fd);
	len[1] = 1;
	line[len[0]] = '\0';
	while (line)
	{
		wall = check_walls(line, len[0], fd);
		free(line);
		line = get_next_line(fd);
		check_len(line, len, wall, fd);
		len[1]++;
	}
	check_size((len[1] - 1) * 64 + 64, len[3], NULL, 0);
	if (close(fd) < 0)
		finish("close", 22);
}

char	check_walls(char *line, int32_t len, int fd)
{
	char	wall;
	char	*aux;

	if (*line != '1' || *(line + len - 1) != '1')
	{
		if (*line == '0' || *(line + len - 1) == '0')
			free_line_and_exit(line, fd, "Map not properly enclosed by walls");
		free_line_and_exit(line, fd, "Forbidden characters found in map");
	}
	aux = line;
	wall = 1;
	while (*aux)
	{
		if (*aux != '1')
			wall = 0;
		if (!ft_strchr("01CEP", *aux))
			free_line_and_exit(line, fd, "Forbidden characters found in map");
		check_p_and_e(*aux, line, fd);
		aux++;
	}
	return (wall);
}

void	set_items_in_window(t_map *map, t_texture *texture, int *con)
{
	mlx_image_t	*temp;
	mlx_t		*mlx;

	temp = NULL;
	if (map->map[con[0]][con[1]] == '1')
		temp = map->img->wall;
	if (map->map[con[0]][con[1]] == 'C')
		temp = map->img->collectable;
	if (map->map[con[0]][con[1]] == 'E')
		temp = map->img->exit;
	if (!temp)
		clean_and_exit(texture, map, "Incorrect map");
	mlx = map->window;
	if (mlx_image_to_window(mlx, temp, con[1] * 64, con[0] * 64) < 0)
		clean_and_exit(texture, map, mlx_strerror(mlx_errno));
}

void	call_check_map(char *map)
{
	check_map(map);
}

void	call_play_game(t_map *map)
{
	play_game(map);
}
