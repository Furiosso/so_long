/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:50:50 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 19:04:54 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_arg(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_map	*map;

	check_arg(argc, argv);
	call_check_map(argv[1]);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		finish("malloc", 1);
	flood_fill(argv[1], map);
	call_play_game(map);
}

static void	check_arg(int argc, char **argv)
{
	if (argc != 2)
		end("Not enough or too many arguments", 2);
	if (!check_extention(argv[1], ".ber"))
		end("Not a .ber document", 3);
	if (!ft_strncmp(".ber", argv[1], 4))
		end("Nameless document", 4);
	check_name(argv[1]);
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

void	get_width_and_height(int32_t *width, int32_t *height)
{
	mlx_t	*mlx;

	mlx = mlx_init(1, 1, "", false);
	if (!mlx)
	{
		if (ft_printf("%s\n", (mlx_strerror(mlx_errno))) < 0)
			end("ft_printf fail", 5);
		exit(EXIT_FAILURE);
	}
	mlx_get_monitor_size(0, width, height);
	mlx_terminate(mlx);
}

void	check_size(int32_t size1, int32_t size2, char *line, int fd)
{
	if (size1 > size2)
		free_line_and_exit(line, fd, "Map provided bigger than monitor");
}
