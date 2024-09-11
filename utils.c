/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:51:18 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/09 15:18:56 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*check_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit (14);
	return (line);
}

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}
