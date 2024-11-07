/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:51:18 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/07 21:28:08 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}

void	end(char *s, int err_key)
{
	if (ft_printf("Error\n%s\n", s) < 0)
		finish("ft_printf", 9);
	exit(err_key);
}

char	*check_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		if (close(fd) < 0)
			finish("close", 10);
		end("void file", 11);
	}
	return (line);
}

void	check_len(char *line, int32_t *len, char wall, int fd)
{
	if (line && (((line[ft_strlen(line) - 1] == '\n')
				&& ft_strlen(line) != (size_t)len[0] + 1)
			|| (line[ft_strlen(line) - 1] != '\n'
				&& ft_strlen(line) != (size_t)len[0])))
		free_line_and_exit(line, fd, "The map provided is not rectangular");
	if (line && line[len[0]] == '\n')
		line[len[0]] = '\0';
	if ((!wall && len[1] == 1) || (!wall && !line))
		free_line_and_exit(line, fd, "The map provided is not rectangular");
}

void	check_name(char *name)
{
	char	*needle;
	char	*ber;

	needle = ft_strrchr(name, '/');
	if (!needle)
		return ;
	ber = ".ber";
	needle++;
	while (*needle && *ber)
	{
		if (*needle != *ber)
			return ;
		needle++;
		ber++;
	}
	end ("Nameless document", 5);
}
