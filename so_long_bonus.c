/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:28:19 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/30 15:28:00 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_arg(int argc, char **argv);
static void	check_map(char *map);
static char	check_walls(char *line, int32_t len, int fd);
static void	check_p_and_e(char c, char *line, int fd);

int	main(int argc, char **argv)
{
	t_map	*map;

	check_arg(argc, argv);
	check_map(argv[1]);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		finish("malloc", 12);
	flood_fill(argv[1], map);
	play_game(map);
}

static void	check_arg(int argc, char **argv)
{
	if (argc != 2)
		end("Not enough or too many arguments", 1);
	if (!check_extention(argv[1], ".ber"))
		end("Not a .ber document", 2);
	if (!ft_strncmp(".ber", argv[1], 4))
		end("Nameless document", 3);
	check_name(argv[1]);
}

static void	check_map(char *map)
{
	int		fd;
	int32_t	len[4];
	char	wall;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		finish("open", 4);
	line = check_first_line(fd);
	get_width_and_height(&len[2], &len[3]);
	len[0] = ft_strlen(line) - 1;
	check_size(len[0] * 64, len[2], line, fd);
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
	check_size((len[1]) * 64, len[3], NULL, 0);
	if (close(fd) < 0)
		finish("close", 11);
}

static char	check_walls(char *line, int32_t len, int fd)
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
		if (!ft_strchr("01CEFP", *aux))
			free_line_and_exit(line, fd, "Forbidden characters found in map");
		check_p_and_e(*aux, line, fd);
		aux++;
	}
	return (wall);
}

static void	check_p_and_e(char c, char *line, int fd)
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
