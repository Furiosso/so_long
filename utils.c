/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:51:18 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/30 19:00:30 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*check_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit (14);
	return (line);
}

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}

void	find_e(t_map *map)
{
	size_t	i;
	size_t	j;
	char	flag;

	flag = 0;
	i = 1;
	while ((*map).map[i])
	{
		j = 1;
		while ((*map).map[i][j])
		{
			if ((*map).map[i][j] == 'E')
			{
				(*map).exit[0] = i;
				(*map).exit[1] = j;
				break ;
			}
			j++;
		}
		if (flag)
			break ;
		i++;
	}
}
