/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:48:02 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/10 12:55:24 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	get_height(char *map);
char	*record_boxes_info(char **copy, char *line, size_t len);
void	clean_copy(char **copy);

char	**copy_map(char *map)
{
	char	**copy;
	size_t	len[2];
	int		fd;
	char	*line;
	size_t	con;

	len[0] = get_height(map);
	copy = ft_calloc(sizeof(char *), len[0]);
	if (!copy)
		exit(15);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		finish("open", 16);
	line = get_next_line(fd);
	len[1] = ft_strlen(line) - 1;
	con = -1;
	while (line)
	{
		copy[++con] = record_boxes_info(copy, line, len[1]);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 19);
	return (copy);
}

size_t	get_height(char *map)
{
	int		fd;
	char	*line;
	size_t	height;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		finish("open", 17);
	line = get_next_line(fd);
	height = 1;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 20);
	return (height);
}

char	*record_boxes_info(char **copy, char *line, size_t len)
{
	size_t	i;
	char	*row;

	row = ft_calloc(sizeof(char), len + 1);
	if (!row)
	{
		clean_copy(copy);
		exit(18);
	}
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
