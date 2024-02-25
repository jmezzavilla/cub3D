/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:46:58 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/25 15:09:49 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	print_sprite_ray(t_sprite *sprite, int stripe)
{
	int	draw_start_y;
	int	draw_end_y;
	int	y;
	int	color;
	t_buffer *img;

	draw_start_y = get_draw_start_y();
	draw_end_y = get_draw_end_y();
	y = draw_start_y;
	img = get_sprite_ray(sprite);
	if (img && gm()->raycast.ray_sprite.trans_y > 0 && stripe > 0 && stripe < WIN_WIDTH
		&& gm()->raycast.ray_sprite.trans_y < gm()->raycast.z_buffer[stripe])
	{
		while (y < draw_end_y)
		{			
			color = get_pixel_color(img, get_tex_x(stripe),
					get_tex_y(y));
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(&gm()->image_buffer, stripe, y, color);
			y++;
		}
	}
}

// calculate width of the sprite
// the conditions in the if are:
// 1) it's in front of camera plane so you don't see things behind you
// 2) it's on the screen (left)
// 3) it's on the screen (right)
// 4) z_buffer, with perpendicular distance
void	raycast_sprites(t_sprite *sprites, t_game *game)
{
	int	draw_start_x;
	int	draw_end_x;
	int	stripe;

	draw_start_x = -game->raycast.ray_sprite.spt_w / 2
		+ game->raycast.ray_sprite.spt_scr_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = game->raycast.ray_sprite.spt_w / 2
		+ game->raycast.ray_sprite.spt_scr_x;
	if (draw_end_x >= WIN_WIDTH)
		draw_end_x = WIN_WIDTH - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		print_sprite_ray(sprites, stripe);
		stripe++;
	}
}

void	draw_raycast_sprites(t_sprite *sprites, t_game *game)
{
	game->raycast.ray_sprite.sprite_x = sprites->pos->x - game->player->pos->x;
	game->raycast.ray_sprite.sprite_y = sprites->pos->y - game->player->pos->y;
	game->raycast.ray_sprite.inv_det = 1.0 / (game->player->plane->x
			* game->player->dir->y - game->player->dir->x
			* game->player->plane->y);
	game->raycast.ray_sprite.trans_x = game->raycast.ray_sprite.inv_det
		* (game->player->dir->y * game->raycast.ray_sprite.sprite_x
			- game->player->dir->x * game->raycast.ray_sprite.sprite_y);
	game->raycast.ray_sprite.trans_y = game->raycast.ray_sprite.inv_det
		* (-game->player->plane->y * game->raycast.ray_sprite.sprite_x
			+ game->player->plane->x * game->raycast.ray_sprite.sprite_y);
	game->raycast.ray_sprite.spt_scr_x = ((WIN_WIDTH / 2) * (1
				+ game->raycast.ray_sprite.trans_x
				/ game->raycast.ray_sprite.trans_y));
	game->raycast.ray_sprite.spt_h = fabs(WIN_HEIGHT
			/ (game->raycast.ray_sprite.trans_y));
	game->raycast.ray_sprite.spt_w = fabs(WIN_HEIGHT
			/ (game->raycast.ray_sprite.trans_y));
	raycast_sprites(sprites, game);
}

void	draw_enemies(t_game *game)
{
	t_list	*cur;
	t_sprite	*sprite;

	cur = game->sprites;
	while (cur)
	{
		sprite = cur->content;
		draw_raycast_sprites(sprite, game);
		cur = cur->next;
	}
}
