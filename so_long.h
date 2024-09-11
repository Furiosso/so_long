/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:06:52 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/11 13:00:49 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "Libft/libft.h"

typedef struct s_box
{
	int				y;
	int				x;
	struct s_box	*next;
}		t_box;

char	*check_first_line(int fd);
void	clean_copy(char **copy);
t_box	*create_box(t_box *queue, int y, int x);
char	**copy_map(char *map);
void	deque(t_box **queue);
void	enque(t_box *queue, int y, int x);
void	flood_fill(char *map);
void	finish(char *s, int err_key);

#endif
