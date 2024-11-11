/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:06:52 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/11 19:17:12 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_box
{
	int				y;
	int				x;
	struct s_box	*next;
}		t_box;

typedef struct s_image
{
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*collectable;
	mlx_image_t	*collectable2;
	mlx_image_t	*exit;
	mlx_image_t	*foe;
	mlx_image_t	*foe2;
}		t_image;

typedef struct s_texture
{
	mlx_texture_t	*background;
	mlx_texture_t	*wall;
	mlx_texture_t	*player;
	mlx_texture_t	*collectable;
	mlx_texture_t	*collectable2;
	mlx_texture_t	*exit;
	mlx_texture_t	*foe;
	mlx_texture_t	*foe2;
}		t_texture;

typedef struct s_map
{
	mlx_t			*window;
	char			**map;
	int32_t			height;
	int32_t			wide;
	int32_t			*player;
	size_t			collectables;
	char			cs_are_found;
	unsigned int	steps;
	mlx_image_t		*counter;
	t_image			*img;
	t_texture		*texture;
}		t_map;

void	call_check_map(char *map);
void	call_play_game(t_map *map);
void	call_set_items_in_window(t_map *map, int *con);
size_t	check_c(char *source, t_map *map);
void	check_exit(t_map *map);
void	check_len(char *line, int32_t *len, char wall, int fd);
char	*check_first_line(int fd);
void	check_name(char *name);
void	check_p_and_e(char c, char *line, int fd);
void	check_size(int32_t size1, int32_t size2, char *line, int fd);
void	choose_direction(t_map *map, char move);
void	clean_and_exit(t_texture *texture, t_map *map, const char *s);
void	clean_copy(char **copy);
void	clean_window(t_map *map, t_image *img, t_texture *texture, mlx_t *mlx);
t_box	*create_box(t_box *queue, int y, int x);
void	copy_line(t_map *map, char **copy, size_t con);
char	**copy_map(char *source, t_map *map);
void	deque(t_box **queue);
void	draw_image(t_map *source, mlx_t *mlx);
void	end(const char *s, int err_key);
void	enque(t_box *queue, int y, int x);
void	flood_fill(char *source, t_map *map);
char	find_p(char **copy, int32_t **origin, t_map *map);
void	finish(const char *s, int err_key);
void	free_line_and_exit(char *line, int fd, const char *s);
void	free_map_and_exit(t_map *map, const char *s, char **copy);
void	free_map_and_finish(t_map *map, const char *s);
void	ft_close_window(void *param);
size_t	get_height(char *map);
void	get_width_and_height(int32_t *width, int32_t *height);
void	move_player(t_map *map, char move);

#endif
