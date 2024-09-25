/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:06:37 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/25 13:29:21 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char **get_map(char *file, size_t *size);

int32_t	play_game(char *file)
{
	mlx_t 	*mlx;
	char	**map;
	size_t	*size;

	size = ft_calloc(sizeof(size_t), 2);
	if (!size)
		exit(20);
	map = get_map(file, size);
	printf("altura: %zu, longitud: %zu\n", size[0], size[1]);
	if (!(mlx = mlx_init(512, 512, "SO LONG", true)))
	{
		ft_printf("%s\n", (mlx_strerror(mlx_errno)));
		return(EXIT_FAILURE);
	}
	clean_copy(map);
	return (EXIT_SUCCESS);
}

char **get_map(char *file, size_t *size)
{
	char **map;

	map = copy_map(file);
	size[0] = 0;
	while (map[size[0]])
	{
		size[1] = 0;
		while (map[size[0]][size[1]])
			size[1]++;
		size[0]++;
	}
	return (map);
}
