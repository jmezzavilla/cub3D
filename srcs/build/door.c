/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:44:49 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/23 18:37:45 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_buffer	*action_door(t_door *door)
{
	if (door->open)
	{
		if (door->animation == 1000000)
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
		if (door->animation == 1000000)
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
	t_door	*door;

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

void	set_door(int y, int x)
{
	t_door	*door;

	door = ft_calloc(sizeof(t_door), 1);
	if (!door)
		error_msg("Memory allocation - door");
	door->open = false;
	door->img_pos = 0;
	door->animation = 0;
	door->pos = set_coord((double)y, (double)x);
	ft_lstadd_back(&gm()->doors, ft_lstnew(door));
}

t_door	*get_door(int y, int x)
{
	t_list	*cur;
	t_door	*door;

	cur = gm()->doors;
	while (cur)
	{
		door = cur->content;
		if (door->pos->x == x && door->pos->y == y)
			return (door);
		cur = cur->next;
	}
	return (NULL);
}

void	build_door(void)
{
	int	x;
	int	y;

	y = 0;
	while (gm()->map[y])
	{
		x = 0;
		while (gm()->map[y][x])
		{
			if (gm()->map[y][x] == 'D')
				set_door(y, x);
			x++;
		}
		y++;
	}
}
