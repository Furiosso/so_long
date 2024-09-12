/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:52:05 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/12 12:05:16 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	check_c(char *map);
size_t	count_cs(char *line);
int	*find_p(char **map);

void	flood_fill(char *map)
{
	size_t	c[2];
	char	e;
	char	**copy;
	int		*origin;
	t_box	*queue;

	c[0] = check_c(map);
	copy = copy_map(map);
	origin = find_p(copy);
	copy[origin[0]][origin[1]] = '0';
	/*int i = 0;
	while (copy[i])
		ft_printf("%s\n", copy[i++]);*/
	e = 0;
	c[1] = 0;
	queue = create_box(NULL, origin[0], origin[1]);
	//t_box	*box;
	while (queue)
	{
		if (copy[queue->y][queue->x] != 'P' && copy[queue->y][queue->x] != '1')
		{
		//	ft_printf("copy[%d][%d]: %c\n", queue->y, queue->x, copy[queue->y][queue->x]);
			if (copy[queue->y][queue->x] == 'C')
				c[1]++;
			if (copy[queue->y][queue->x] == 'E')
				e++;
			copy[queue->y][queue->x] = 'P';
			enque(queue, queue->y + 1, queue->x);
			enque(queue, queue->y - 1, queue->x);
			enque(queue, queue->y, queue->x + 1);
			enque(queue, queue->y, queue->x - 1);
		}	
		deque(&queue);
		/*box = queue;
		while (box)
		{
			ft_printf("copy[%d][%d]: %c\n", box->y, box->x, copy[box->y][box->x]);
			box = box->next;
		}
		ft_printf("\n");*/
	}
	int i = 0;
	while (copy[i])
		ft_printf("%s\n", copy[i++]);
	if (!e || c[1] != c[0])
		exit(21);
	free(origin);
	clean_copy(copy);
}

size_t	check_c(char *map)
{
	int		fd;
	size_t	c;
	char	*line;

	fd = open(map, O_RDWR);
	if (fd < 0)
		finish("open", 11);
	c = 0;
	line = check_first_line(fd);
	while (line)
	{
		c += count_cs(line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		finish("close", 12);
	if (!c)
		exit(13);
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

int	*find_p(char **map)
{
	int		*origin;
	char	flag;

	flag = 0;
	origin = ft_calloc(sizeof(int), 2);
	if (!origin)
		exit(23);
	origin[0] = 1;
	while (map[origin[0]])
	{
		origin[1] = 1;
		while (map[origin[0]][origin[1]])
		{
			if (map[origin[0]][origin[1]] == 'P')
			{
				flag = 1;
				break ;
			}
			origin[1]++;
		}
		if (flag)
			break ;
		origin[0]++;
	}
	return (origin);
}
