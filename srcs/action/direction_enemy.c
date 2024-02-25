/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:24:53 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/25 15:17:27 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	kill_player(t_sprite *sprite, t_player *player)
{
	if ((int)sprite->pos->x == (int)player->pos->x
		&& (int)sprite->pos->y == (int)player->pos->y)
	{
		prt("Try again\n");
		quit();
	}
}

t_coord	new_pos(t_sprite *sprite, t_player *player)
{
	t_coord	enemy_dir;
	double	dx;
	double	dy;
	double	length;

	dx = player->pos->x - sprite->pos->x;
	dy = player->pos->y - sprite->pos->y;
	length = sqrt(dx * dx + dy * dy);
	enemy_dir.x = (dx / length);
	enemy_dir.y = (dy / length);
	return (enemy_dir);
}

void	move_enemy(char **map, t_sprite *sprite, t_player *player)
{
	t_coord	enemy_dir;
	double	new_x;
	double	new_y;

	enemy_dir = new_pos(sprite, player);
	new_x = sprite->pos->x + enemy_dir.x * 0.015;
	new_y = sprite->pos->y + enemy_dir.y * 0.015;
	if (map[(int)(new_y + WALL_DISTANCE)][(int)(new_x + WALL_DISTANCE)] != '1'
		&& map[(int)(new_y + WALL_DISTANCE)][(int)(new_x
			- WALL_DISTANCE)] != '1' && map[(int)(new_y
			- WALL_DISTANCE)][(int)(new_x + WALL_DISTANCE)] != '1'
		&& map[(int)(new_y - WALL_DISTANCE)][(int)(new_x
			- WALL_DISTANCE)] != '1')
	{
		sprite->pos->y = new_y;
		sprite->pos->x = new_x;
		kill_player(sprite, player);
	}
}

void	move_enemies(t_game *game)
{
	t_list	*lst;
	t_sprite	*sprite;
	int		move;

	move = 0;
	lst = game->sprites;
	while (game->sprites && lst)
	{
		sprite = lst->content;
		if(sprite->type == 'M')
		{
			move = rand() % 2;
			if (move == 1)
				move_enemy(game->map, sprite, game->player);
		}
		lst = lst->next;
	}
}
