/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:44:49 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/22 23:21:33 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void action_door(t_door *door)
{
	//int i;
	//int animation;
	if(!door->open)
	{
	//	i = 4;
	//	animation = 0;
		door->open = true;
		/*while (door->img_pos < i)
		{
			if (animation == 4)
			{
				if (door->img_pos != i)
				{
					door->img = gm()->scene->exit[i];
					door->img_pos++;
				}
					
				animation = 0;
			}
			else
				animation++;	
		}*/
		door->img = gm()->scene->exit[3];
	}else
	{
		door->open = false;
		door->img = gm()->scene->exit[0];
	}
}

void open_door()
{
	int	y;
	int	x; 
	t_door *door;
	t_player * player;

	player = gm()->player;

	x = player->pos->x + player->dir->x * MOVE;
	y = player->pos->y + player->dir->y * MOVE - 1;
	door = get_door(y,x);
	if (door)
		action_door(door);
	y =	player->pos->x - (player->plane->x * MOVE);
	x = player->pos->y - (player->plane->y * MOVE) - 1;
	door = get_door(y,x);
	if (door)
		action_door(door);
	x = player->pos->x - player->dir->x * MOVE;
	y = player->pos->y - player->dir->y * MOVE + 1;
	door = get_door(y,x);
	if (door)
		action_door(door);
	y =	player->pos->x - (player->plane->x * MOVE);
	x = player->pos->y - (player->plane->y * MOVE) + 1;
	door = get_door(y,x);
	if (door)
		action_door(door);
}

void set_door(int y, int x)
{
	t_door *door;
	door = ft_calloc(sizeof(t_door),1);
	if (!door)
		error_msg("Memory allocation - door");
	door->open = false;
	door->img_pos = 0;
	door->pos = set_coord((double) y, (double) x);
	door->img = gm()->scene->exit[0];
	ft_lstadd_back(&gm()->doors,ft_lstnew(door));
}

t_door *get_door(int y, int x)
{
	t_list *cur;
	t_door *door;
	
	cur = gm()->doors;
	while (cur)
	{
		door = cur->content;
		if(door->pos->x == x && door->pos->y == y )
			return door;
		cur = cur->next;
	}
	return NULL;
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
				set_door(y,x);
			x++;
		}
		y++;
	}
}
