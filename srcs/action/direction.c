/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:53 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 23:42:53 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_right(char **map, t_player *player)
{
	double	x;
	double	y;

	x = player->pos->x;
	y = player->pos->y;
	player->pos->x += (player->plane->x * MOVE);
	player->pos->y += (player->plane->y * MOVE);
	check_colision(map, x, y, player->pos);
}

void	move_left(char **map, t_player *player)
{
	double	x;
	double	y;

	x = player->pos->x;
	y = player->pos->y;
	player->pos->x -= (player->plane->x * MOVE);
	player->pos->y -= (player->plane->y * MOVE);
	check_colision(map, x, y, player->pos);
}

void	move_front(char **map, t_player *player)
{
	double	x;
	double	y;

	x = player->pos->x;
	y = player->pos->y;
	player->pos->x += player->dir->x * MOVE;
	player->pos->y += player->dir->y * MOVE;
	check_colision(map, x, y, player->pos);
}

void	move_back(char **map, t_player *player)
{
	double	x;
	double	y;

	x = player->pos->x;
	y = player->pos->y;
	player->pos->x -= player->dir->x * MOVE;
	player->pos->y -= player->dir->y * MOVE;
	check_colision(map, x, y, player->pos);
}
