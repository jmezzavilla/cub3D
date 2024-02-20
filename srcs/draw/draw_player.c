/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:07:23 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 23:46:50 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_player *player)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = player->dir->x;
	oldplane_x = player->plane->x;
	player->dir->x = player->dir->x * cos(-MOVE) - player->dir->y * sin(-MOVE);
	player->dir->y = olddir_x * sin(-MOVE) + player->dir->y * cos(-MOVE);
	player->plane->x = player->plane->x * cos(-MOVE) - player->plane->y
		* sin(-MOVE);
	player->plane->y = oldplane_x * sin(-MOVE) + player->plane->y * cos(-MOVE);
}

void	rotate_right(t_player *player)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = player->dir->x;
	oldplane_x = player->plane->x;
	player->dir->x = player->dir->x * cos(MOVE) - player->dir->y * sin(MOVE);
	player->dir->y = olddir_x * sin(MOVE) + player->dir->y * cos(MOVE);
	player->plane->x = player->plane->x * cos(MOVE) - player->plane->y
		* sin(MOVE);
	player->plane->y = oldplane_x * sin(MOVE) + player->plane->y * cos(MOVE);
}

void	event_player(t_game *game)
{
	if (game->controls.up == W_KEY)
		move_front(game, game->player);
	if (game->controls.down == S_KEY)
		move_back(game, game->player);
	if (game->controls.left == A_KEY)
		move_left(game, game->player);
	if (game->controls.right == D_KEY)
		move_right(game, game->player);
	if (game->controls.rotate_right == RIGHT_KEY)
		rotate_right(game->player);
	if (game->controls.rotate_left == LEFT_KEY)
		rotate_left(game->player);
}
