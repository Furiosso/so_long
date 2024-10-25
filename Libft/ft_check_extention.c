/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_extention.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:00:44 by dagimeno          #+#    #+#             */
/*   Updated: 2024/10/25 13:08:48 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	check_extention(char *name, char *extention)
{
	size_t	index[2];

	index[0] = ft_strlen(name) - 1;
	index[1] = ft_strlen(extention) - 1;
	while (name[index[0]] && extention[index[1]])
	{
		if (name[index[0]--] != extention[index[1]--])
			return (0);
	}
	return (1);
}
