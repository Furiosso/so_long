/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:23:33 by dagimeno          #+#    #+#             */
/*   Updated: 2024/09/13 17:15:14 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_queue(t_box *queue);

t_box	*create_box(t_box *queue, int y, int x)
{
	t_box	*box;

	box = ft_calloc(sizeof(t_box), 1);
	if (!box)
	{
		if (queue)
			clean_queue(queue);
		exit(22);
	}
	box->y = y;
	box->x = x;
	box->next = NULL;
	return (box);
}

void	enque(t_box *queue, int y, int x)
{
	t_box	*box;
	t_box	*aux;

	box = create_box(queue, y, x);
	aux = queue;
	while (aux->next)
		aux = aux->next;
	aux->next = box;
}

void	deque(t_box **queue)
{
	t_box	*aux;

	aux = *queue;
	*queue = aux->next;
	aux->next = NULL;
	free(aux);
}

void	clean_queue(t_box *queue)
{
	t_box	*aux;

	while (queue)
	{
		aux = queue->next;
		free(queue);
		queue = aux;
	}
}
