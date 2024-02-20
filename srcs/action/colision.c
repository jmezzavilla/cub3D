/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:44 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 23:00:35 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_right_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y + (player->dir->x * MOVE);
	x = player->pos->x - (player->dir->y * MOVE);
	return (game->map[y][x] == '1');
}

int	is_left_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y - (player->dir->x * MOVE);
	x = player->pos->x + (player->dir->y * MOVE);
	return (game->map[y][x] == '1');
}

int	is_front_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y + (player->dir->y * MOVE);
	x = player->pos->x + (player->dir->x * MOVE);
	return (game->map[y][x] == '1');
}

int	is_back_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y - (player->dir->y * MOVE);
	x = player->pos->x - (player->dir->x * MOVE);
	return (game->map[y][x] == '1');
}
