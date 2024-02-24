/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:24:53 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/24 17:25:35 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	kill_player(t_enemy *enemy, t_player *player)
{
	if ((int)enemy->pos->x == (int)player->pos->x
		&& (int)enemy->pos->y == (int)player->pos->y)
	{
		prt("You loser a game, try again\n");
		quit();
	}
}

t_coord	new_pos(t_enemy *enemy, t_player *player)
{
	t_coord	enemy_dir;
	double	dx;
	double	dy;
	double	length;

	dx = player->pos->x - enemy->pos->x;
	dy = player->pos->y - enemy->pos->y;
	length = sqrt(dx * dx + dy * dy);
	enemy_dir.x = (dx / length);
	enemy_dir.y = (dy / length);
	return (enemy_dir);
}

void	move_enemy(char **map, t_enemy *enemy, t_player *player)
{
	t_coord	enemy_dir;
	double	new_x;
	double	new_y;

	enemy_dir = new_pos(enemy, player);
	new_x = enemy->pos->x + enemy_dir.x * 0.015;
	new_y = enemy->pos->y + enemy_dir.y * 0.015;
	if (map[(int)(new_y + WALL_DISTANCE)][(int)(new_x + WALL_DISTANCE)] != '1'
		&& map[(int)(new_y + WALL_DISTANCE)][(int)(new_x
			- WALL_DISTANCE)] != '1' && map[(int)(new_y
			- WALL_DISTANCE)][(int)(new_x + WALL_DISTANCE)] != '1'
		&& map[(int)(new_y - WALL_DISTANCE)][(int)(new_x
			- WALL_DISTANCE)] != '1')
	{
		enemy->pos->y = new_y;
		enemy->pos->x = new_x;
		kill_player(enemy, player);
	}
}

void	move_enemies(t_game *game)
{
	t_list	*lst;
	t_enemy	*enemy;
	int		move;

	move = 0;
	lst = game->enemies;
	while (game->enemies && lst)
	{
		enemy = lst->content;
		move = rand() % 2;
		if (move == 1)
			move_enemy(game->map, enemy, game->player);
		if (!enemy && !game)
			return ;
		lst = lst->next;
	}
}
