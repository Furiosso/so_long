/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:53 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/03 19:49:06 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static size_t	check_c(char *source, t_map *map);
static void		count_cs(char *line, size_t *c);
static char		find_p(char **copy, int32_t **origin, t_map *map);
static void		bfs(char **copy, t_box *queue, size_t c, t_map *map);

void	flood_fill(char *source, t_map *map)
{
	char	**copy;
	int32_t	*origin;
	t_box	*queue;

	map->collectables = check_c(source, map);
	map->height = get_height(source);
	map->map = ft_calloc(sizeof(char *), map->height + 1);
	origin = ft_calloc(sizeof(int32_t), 2);
	map->player = ft_calloc(sizeof(int32_t), 2);
	if (!origin || !map->map || !map->player)
		free_map_and_finish(map, "malloc");
	copy = copy_map(source, map);
	if (!find_p(copy, &origin, map))
		free_map_and_exit(map, "Player not found", copy);
	copy[origin[0]][origin[1]] = '0';
	queue = create_box(NULL, origin[0], origin[1]);
	free(origin);
	bfs(copy, queue, map->collectables, map);
	clean_copy(copy);
}

static size_t	check_c(char *source, t_map *map)
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

static char	find_p(char **copy, int32_t **origin, t_map *map)
{
	/*char	flag;

	flag = 0;*/
	(*origin)[0] = 1;
	while (copy[(*origin)[0]])
	{
		(*origin)[1] = 1;
		while (copy[(*origin)[0]][(*origin)[1]])
		{
			if (copy[(*origin)[0]][(*origin)[1]] == 'P')
			{
				//flag = 1;
				map->player[0] = (*origin)[0];
				map->player[1] = (*origin)[1];
				//break ;
				return (1);
			}
			(*origin)[1]++;
		}
		/*if (flag)
			break ;*/
		(*origin)[0]++;
	}
	return (0);
}

static void	bfs(char **copy, t_box *queue, size_t c, t_map *map)
{
	int		e;
	size_t	c_count;

	c_count = 0;
	e = 0;
	while (queue)
	{
		if (copy[queue->y][queue->x] != 'P' && copy[queue->y][queue->x] != '1'
				&& copy[queue->y][queue->x] != 'F')
		{
			if (copy[queue->y][queue->x] == 'C')
				c_count++;
			if (copy[queue->y][queue->x] == 'E')
				e++;
			copy[queue->y][queue->x] = 'P';
			enque(queue, queue->y + 1, queue->x);
			enque(queue, queue->y - 1, queue->x);
			enque(queue, queue->y, queue->x + 1);
			enque(queue, queue->y, queue->x - 1);
		}
		deque(&queue);
	}
	if (!e || c != c_count)
		free_map_and_exit(map, "Irresolvable map", copy);
}
