/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:48:02 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:29 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	get_height(char *map);
char	*record_boxes_info(char *line, size_t len);
void	clean_copy(char **copy);

char	**copy_map(char *source, t_map *map)
{
	char	**copy;
	int		fd;
	char	*line;
	size_t	con;

	copy = ft_calloc(sizeof(char *), (*map).height);
	if (!copy)
		finish("malloc", 14);
	fd = open(source, O_RDONLY);
	if (fd < 0)
		finish("open", 15);
	line = get_next_line(fd);
	(*map).wide = ft_strlen(line) - 1;
	con = -1;
	while (line)
	{
		copy[++con] = record_boxes_info(line, (*map).wide);
		(*map).map[con] = ft_strdup(copy[con]);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 17);
	return (copy);
}

size_t	get_height(char *map)
{
	int		fd;
	char	*line;
	size_t	height;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		finish("open", 18);
	line = get_next_line(fd);
	height = 1;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 19);
	return (height);
}

char	*record_boxes_info(char *line, size_t len)
{
	size_t	i;
	char	*row;

	row = ft_calloc(sizeof(char), len + 1);
	if (!row)
		finish("malloc", 16);
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
