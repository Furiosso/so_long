/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:30:49 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 21:15:55 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "so_long.h"

void	charge_banner(t_map *map, t_texture *texture);
void	check_enemies(t_map *map);
void	check_map(char *map);
char	check_walls(char *line, int32_t len, int fd);
void	disable_images(mlx_image_t *collectable, mlx_image_t *foe);
void	ft_animation(void *param);
void	flood_fill(char *source, t_map *map);
void	play_game(t_map *map);
void	put_to_win(t_map *map, mlx_image_t *temp, int *con, t_texture *t);
void	set_items_in_window(t_map *map, t_texture *texture, int *con);

#endif
