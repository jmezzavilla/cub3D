/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:46:58 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/25 15:11:31 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_draw_start_y(void)
{
	int	draw_start_y;

	draw_start_y = -gm()->raycast.ray_sprite.spt_h / 2 + WIN_HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	return (draw_start_y);
}

int	get_draw_end_y(void)
{
	int	draw_end_y;

	draw_end_y = gm()->raycast.ray_sprite.spt_h / 2 + WIN_WIDTH / 2;
	if (draw_end_y >= WIN_HEIGHT)
		draw_end_y = WIN_HEIGHT - 1;
	return (draw_end_y);
}

int	get_tex_x(int stripe)
{
	int	tex_x;

	tex_x = (256 * (stripe - (-gm()->raycast.ray_sprite.spt_w / 2
					+ gm()->raycast.ray_sprite.spt_scr_x)) * BLOCK_PIXEL
			/ gm()->raycast.ray_sprite.spt_w) / 256;
	return (tex_x);
}

double	get_tex_y(int y)
{
	int	d;
	int	tex_y;

	d = y * 256 - WIN_HEIGHT * 128 + gm()->raycast.ray_sprite.spt_h * 128;
	tex_y = ((d * BLOCK_PIXEL) / (gm())->raycast.ray_sprite.spt_h) / 256;
	return (tex_y);
}
t_buffer	*get_sprite_ray(t_sprite *sprite)
{
	if(sprite->type == 'M')
		return action_enemy(sprite);
	if(sprite->type == 'D')
		return NULL;
	return &sprite->img;
}
