/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:44:49 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/26 11:46:20 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_buffer	*action_door(t_sprite *door)
{
	if(!door)
		return NULL;
	if (door->open)
	{
		if (door->animation == 1000)
		{
			if (door->img_pos < TOTAL_SPRITE_EXIT - 1)
				door->img_pos += 1;
			door->animation = 0;
		}
		else
			door->animation++;
	}
	else
	{
		if (door->animation == 1000)
		{
			if (door->img_pos != 0)
				door->img_pos -= 1;
			door->animation = 0;
		}
		else
			door->animation++;
	}
	return (&gm()->scene->exit[door->img_pos]);
}

void	open_door(t_player *player)
{
	int		y;
	int		x;
	t_sprite	*door;

	x = player->pos->x + player->dir->x * MOVE;
	y = player->pos->y + player->dir->y * MOVE - 1;
	door = get_door(y, x);
	if (door)
		door->open = !door->open;
	y = player->pos->x - (player->plane->x * MOVE);
	x = player->pos->y - (player->plane->y * MOVE) - 1;
	door = get_door(y, x);
	if (door)
		door->open = !door->open;
	x = player->pos->x - player->dir->x * MOVE;
	y = player->pos->y - player->dir->y * MOVE + 1;
	door = get_door(y, x);
	if (door)
		door->open = !door->open;
	y = player->pos->x - (player->plane->x * MOVE);
	x = player->pos->y - (player->plane->y * MOVE) + 1;
	door = get_door(y, x);
	if (door)
		door->open = !door->open;
}

t_sprite	*get_door(int y, int x)
{
	t_list	*cur;
	t_sprite	*door;

	cur = gm()->sprites;
	while (cur)
	{
		door = cur->content;
		int mx = door->pos->x;
		int my = door->pos->y;
		if (mx == x &&  my == y && door->type == 'D')
			return (door);
		cur = cur->next;
	}
	return (NULL);
}

