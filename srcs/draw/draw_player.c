/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:07:23 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/22 14:42:24 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this functions rotate the player direction and plane using cos/sin
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
		move_front(game->map, game->player);
	if (game->controls.down == S_KEY)
		move_back(game->map, game->player);
	if (game->controls.left == A_KEY)
		move_left(game->map, game->player);
	if (game->controls.right == D_KEY)
		move_right(game->map, game->player);
	if (game->controls.rotate_right == RIGHT_KEY)
		rotate_right(game->player);
	if (game->controls.rotate_left == LEFT_KEY)
		rotate_left(game->player);
}
