/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:53 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 17:00:24 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
