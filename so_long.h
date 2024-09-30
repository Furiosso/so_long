/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:06:52 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/30 18:50:13 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_box
{
	int				y;
	int				x;
	struct s_box	*next;
}		t_box;

typedef struct s_map
{
	char	**map;
	size_t	height;
	size_t	wide;
	size_t	*player;
	size_t	collectables;
	size_t	*exit;
	size_t	steps;
}		t_map;

typedef struct s_texture
{
	mlx_texture_t	*background;
	mlx_texture_t	*wall;
	mlx_texture_t	*player;
	mlx_texture_t	*collectable;
	mlx_texture_t	*exit;
}		t_texture;

typedef struct s_image
{
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*collectable;
	mlx_image_t	*exit;
}		t_image;

char	*check_first_line(int fd);
void	clean_copy(char **copy);
void	clean_window(t_map *map, t_image *img, t_texture *texture, mlx_t *mlx);
t_box	*create_box(t_box *queue, int y, int x);
size_t	get_height(char *map);
char	**copy_map(char *source, t_map *map);
void	deque(t_box **queue);
void	draw_image(char **map, mlx_t *mlx, t_image *img);
void	enque(t_box *queue, int y, int x);
void	flood_fill(char *source, t_map *map);
void	find_e(t_map *map);
void	finish(char *s, int err_key);
int32_t	play_game(t_map *map);

#endif
