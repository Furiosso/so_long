/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:01:49 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 17:17:40 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	count_cs(char *line, size_t *c);

size_t	check_c(char *source, t_map *map)
{
	int		fd;
	size_t	c;
	char	*line;

	fd = open(source, O_RDWR);
	if (fd < 0)
		free_map_and_finish(map, "open");
	c = 0;
	line = check_first_line(fd);
	while (line)
	{
		count_cs(line, &c);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		free_map_and_finish(map, "close");
	if (!c)
		free_map_and_exit(map, "Collectables not found", NULL);
	return (c);
}

static void	count_cs(char *line, size_t *c)
{
	while (*line)
	{
		if (*line == 'C')
			(*c)++;
		line++;
	}
}

char	find_p(char **copy, int32_t **origin, t_map *map)
{
	(*origin)[0] = 1;
	while (copy[(*origin)[0]])
	{
		(*origin)[1] = 1;
		while (copy[(*origin)[0]][(*origin)[1]])
		{
			if (copy[(*origin)[0]][(*origin)[1]] == 'P')
			{
				map->player[0] = (*origin)[0];
				map->player[1] = (*origin)[1];
				return (1);
			}
			(*origin)[1]++;
		}
		(*origin)[0]++;
	}
	return (0);
}
