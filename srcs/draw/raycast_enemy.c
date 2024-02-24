/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:46:58 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/24 02:38:18 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// calculate width of the sprite
// the conditions in the if are:
// 1) it's in front of camera plane so you don't see things behind you
// 2) it's on the screen (left)
// 3) it's on the screen (right)
// 4) z_buffer, with perpendicular distance
void	raycast_enemy(t_enemy *enemy, t_game *game)
{
	int	draw_start_x;
	int	draw_end_x;
	int	stripe;

	draw_start_x = -game->raycast.ray_enemey.spt_w / 2
		+ game->raycast.ray_enemey.spt_scr_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = game->raycast.ray_enemey.spt_w / 2
		+ game->raycast.ray_enemey.spt_scr_x;
	if (draw_end_x >= WIN_WIDTH)
		draw_end_x = WIN_WIDTH - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		print_enemey_ray(enemy, stripe);
		stripe++;
	}
}

void	draw_raycast_enemy(t_enemy *enemy, t_game *game)
{
	game->raycast.ray_enemey.sprite_x = enemy->pos->x - game->player->pos->x;
	game->raycast.ray_enemey.sprite_y = enemy->pos->y - game->player->pos->y;
	game->raycast.ray_enemey.inv_det = 1.0 / (game->player->plane->x
			* game->player->dir->y - game->player->dir->x
			* game->player->plane->y);
	game->raycast.ray_enemey.trans_x = game->raycast.ray_enemey.inv_det
		* (game->player->dir->y * game->raycast.ray_enemey.sprite_x
			- game->player->dir->x * game->raycast.ray_enemey.sprite_y);
	game->raycast.ray_enemey.trans_y = game->raycast.ray_enemey.inv_det
		* (-game->player->plane->y * game->raycast.ray_enemey.sprite_x
			+ game->player->plane->x * game->raycast.ray_enemey.sprite_y);
	game->raycast.ray_enemey.spt_scr_x = ((WIN_WIDTH / 2) * (1
				+ game->raycast.ray_enemey.trans_x
				/ game->raycast.ray_enemey.trans_y));
	game->raycast.ray_enemey.spt_h = fabs(WIN_HEIGHT
			/ (game->raycast.ray_enemey.trans_y));
	game->raycast.ray_enemey.spt_w = fabs(WIN_HEIGHT
			/ (game->raycast.ray_enemey.trans_y));
	raycast_enemy(enemy, game);
}

void	draw_enemies(t_game *game)
{
	t_list	*cur;
	t_enemy	*enemy;

	cur = game->enemies;
	while (cur)
	{
		enemy = cur->content;
		draw_raycast_enemy(enemy, game);
		cur = cur->next;
	}
}
