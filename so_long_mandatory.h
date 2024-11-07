/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mandatory.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:11:44 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 21:10:30 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_MANDATORY_H
# define SO_LONG_MANDATORY_H

# include "so_long.h"

void	check_map(char *map);
char	check_walls(char *line, int32_t len, int fd);
void	flood_fill(char *source, t_map *map);
void	play_game(t_map *map);
void	set_items_in_window(t_map *map, t_texture *texture, int *con);

#endif