/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:51:18 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/03 13:11:25 by dagimeno         ###   ########.fr       */
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

void	check_len(char *line, size_t *len, char wall)
{
	if (line && (((line[ft_strlen(line) - 1] == '\n')
				&& ft_strlen(line) != len[0] + 1)
			|| (line[ft_strlen(line) - 1] != '\n'
				&& ft_strlen(line) != len[0])))
		end("The map provided is not rectangular", 6);
	if (line && line[len[0]] == '\n')
		line[len[0]] = '\0';
	if ((!wall && len[1] == 1) || (!wall && !line))
		end("The map provided is not properly enclosed by walls", 4);
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
