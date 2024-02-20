/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:53 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 22:50:13 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_right(t_game *game, t_player *player)
{
	if (!is_right_wall(game, player))
	{
		player->pos->x += (player->plane->x * MOVE);
		player->pos->y += (player->plane->y * MOVE);
	}
}

void	move_left(t_game *game, t_player *player)
{
	if (!is_left_wall(game, player))
	{
		player->pos->x -= (player->plane->x * MOVE);
		player->pos->y -= (player->plane->y * MOVE);
	}
}

void	move_front(t_game *game, t_player *player)
{
	if (!is_front_wall(game, player))
	{
		player->pos->x += (player->dir->x * MOVE);
		player->pos->y += (player->dir->y * MOVE);
	}
}

void	move_back(t_game *game, t_player *player)
{
	if (!is_back_wall(game, player))
	{
		player->pos->x -= (player->dir->x * MOVE);
		player->pos->y -= (player->dir->y * MOVE);
	}
}
