/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:50 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/15 14:02:30 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_arg(int argc, char **argv);
static void	check_map(char *map);
static char	check_walls(char *line, size_t len, int fd);
static void	check_p_and_e(char c, char *line, int fd);

int	main(int argc, char **argv)
{
	t_map	*map;

	check_arg(argc, argv);
	check_map(argv[1]);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		finish("malloc", 70);
	flood_fill(argv[1], map);
	play_game(map);
}

static void	check_arg(int argc, char **argv)
{
	if (argc != 2)
		end("Not enough or too many arguments", 1);
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		end("Not a .ber document", 2);
	if (!ft_strncmp(".ber", argv[1], 4))
		end("Nameless document", 41);
}

static void	check_map(char *map)
{
	int		fd;
	size_t	len[2];
	char	wall;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		finish("open", 3);
	line = check_first_line(fd);
	len[0] = ft_strlen(line) - 1;
	len[1] = 1;
	line[len[0]] = '\0';
	while (line)
	{
		wall = check_walls(line, len[0], fd);
		free(line);
		line = get_next_line(fd);
		check_len(line, len, wall, fd);
		len[1]++;
	}
	if (close(fd) < 0)
		finish("close", 5);
}

static char	check_walls(char *line, size_t len, int fd)
{
	char	wall;
	char	*aux;

	if (*line != '1' || *(line + len - 1) != '1')
	{
		if (*line == '0' || *(line + len - 1) == '0')
			free_line_and_exit(line, fd, "Map not properly enclosed by walls");
		free_line_and_exit(line, fd, "Forbidden characters found in map");
	}
	aux = line;
	wall = 1;
	while (*aux)
	{
		if (*aux != '1')
			wall = 0;
		if (!ft_strchr("01CEP", *aux))
			free_line_and_exit(line, fd, "Forbidden characters found in map");
		check_p_and_e(*aux, line, fd);
		aux++;
	}
	return (wall);
}

void	check_p_and_e(char c, char *line, int fd)
{
	static int	e = 0;
	static int	p = 0;

	if (c == 'E')
		e++;
	if (c == 'P')
		p++;
	if (e > 1 || p > 1)
		free_line_and_exit(line, fd,
			"Too many players or too many exits found");
}
