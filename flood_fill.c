/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:52:05 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/02 18:18:55 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	check_c(char *map);
size_t	count_cs(char *line);
void	find_p(char **copy, int32_t **origin, t_map *map);
void	bfs(char **copy, t_box *queue, size_t c);

void	flood_fill(char *source, t_map *map)
{
	char	**copy;
	int32_t	*origin;
	t_box	*queue;

	(*map).collectables = check_c(source);
	(*map).height = get_height(source);
	(*map).map = ft_calloc(sizeof(char *), (*map).height);
	origin = ft_calloc(sizeof(int32_t), 2);
	(*map).player = ft_calloc(sizeof(int32_t), 2);
	(*map).exit = ft_calloc(sizeof(int32_t), 2);
	if (!origin || !(*map).map || !(*map).player || !(*map).exit)
		finish("malloc", 20);
	copy = copy_map(source, map);
	find_p(copy, &origin, map);
	copy[origin[0]][origin[1]] = '0';
	queue = create_box(NULL, origin[0], origin[1]);
	free(origin);
	bfs(copy, queue, (*map).collectables);
	clean_copy(copy);
	find_e(map);
}

size_t	check_c(char *source)
{
	int		fd;
	size_t	c;
	char	*line;

	fd = open(source, O_RDWR);
	if (fd < 0)
		finish("open", 21);
	c = 0;
	line = check_first_line(fd);
	while (line)
	{
		c += count_cs(line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 22);
	if (!c)
		end("Collectables not found", 23);
	return (c);
}

size_t	count_cs(char *line)
{
	size_t	c;

	c = 0;
	while (*line)
	{
		if (*line == 'C')
			c++;
		line++;
	}
	return (c);
}

void	find_p(char **copy, int32_t **origin, t_map *map)
{
	char	flag;

	flag = 0;
	(*origin)[0] = 1;
	while (copy[(*origin)[0]])
	{
		(*origin)[1] = 1;
		while (copy[(*origin)[0]][(*origin)[1]])
		{
			if (copy[(*origin)[0]][(*origin)[1]] == 'P')
			{
				flag = 1;
				(*map).player[0] = (*origin)[0];
				(*map).player[1] = (*origin)[1];
				break ;
			}
			(*origin)[1]++;
		}
		if (flag)
			break ;
		(*origin)[0]++;
	}
}

void	bfs(char **copy, t_box *queue, size_t c)
{
	int		e;
	size_t	c_count;

	c_count = 0;
	e = 0;
	while (queue)
	{
		if (copy[queue->y][queue->x] != 'P' && copy[queue->y][queue->x] != '1')
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
		end("Irresolvable map", 24);
}
