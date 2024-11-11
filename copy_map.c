/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:48:02 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 18:47:47 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t		get_height(char *map);
static char	*record_boxes_info(char *line, size_t len);

char	**copy_map(char *source, t_map *map)
{
	char	**copy;
	int		fd;
	char	*line;
	size_t	con;

	copy = ft_calloc(sizeof(char *), map->height);
	if (!copy)
		finish("ft_calloc", 12);
	fd = open(source, O_RDONLY);
	if (!copy || fd < 0)
		finish("open", 13);
	line = get_next_line(fd);
	map->wide = ft_strlen(line) - 1;
	con = -1;
	while (line)
	{
		copy[++con] = record_boxes_info(line, map->wide);
		copy_line(map, copy, con);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 14);
	return (copy);
}

size_t	get_height(char *map)
{
	int		fd;
	char	*line;
	size_t	height;

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		finish("open", 15);
	}
	line = get_next_line(fd);
	height = 1;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
	{
		free(map);
		finish("close", 16);
	}
	return (height);
}

static char	*record_boxes_info(char *line, size_t len)
{
	size_t	i;
	char	*row;

	row = ft_calloc(sizeof(char), len + 1);
	if (!row)
		finish("ft_calloc", 17);
	i = 0;
	while (i < len)
	{
		row[i] = line[i];
		i++;
	}
	row[i] = 0;
	return (row);
}

void	clean_copy(char **copy)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}
