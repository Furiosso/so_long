/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:50 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/30 19:51:20 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arg(int argc, char **argv);
void	check_map(char *map);
char	check_walls(char *line, size_t len);
void	check_p_and_e(char c);

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

void	check_arg(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		exit(2);
}

void	check_map(char *map)
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
		wall = check_walls(line, len[0]);
		free(line);
		line = get_next_line(fd);
		if (line && line[len[0]] == '\n')
			line[len[0]] = '\0';
		if ((!wall && len[1] == 1) || (!wall && !line))
			exit(4);
		len[1]++;
	}
	if (close(fd) < 0)
		finish("close", 5);
}

char	check_walls(char *line, size_t len)
{
	char	*allowed;
	char	wall;

	if (line && ft_strlen(line) != len)
		exit(6);
	if (*line != '1')
		exit(7);
	if (*(line + len - 1) != '1')
		exit(8);
	wall = 1;
	allowed = "01CEP";
	while (*line)
	{
		if (*line != '1')
			wall = 0;
		if (!ft_strchr(allowed, *line))
			exit(9);
		check_p_and_e(*line);
		line++;
	}
	return (wall);
}

void	check_p_and_e(char c)
{
	static int	e = 0;
	static int	p = 0;

	if (c == 'E')
		e++;
	if (c == 'P')
		p++;
	if (e > 1 || p > 1)
		exit(10);
}
