/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:51:18 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/02 18:44:48 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}

void	end(char *s, int err_key)
{
	ft_printf("Error\n%s\n", s);
	exit(err_key);
}

char	*check_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		end ("void file", 40);
	return (line);
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
