/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemy2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:46:58 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/24 02:37:57 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_draw_start_y(void)
{
	int	draw_start_y;

	draw_start_y = -gm()->raycast.ray_enemey.spt_h / 2 + WIN_HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	return (draw_start_y);
}

int	get_draw_end_y(void)
{
	int	draw_end_y;

	draw_end_y = gm()->raycast.ray_enemey.spt_h / 2 + WIN_WIDTH / 2;
	if (draw_end_y >= WIN_HEIGHT)
		draw_end_y = WIN_HEIGHT - 1;
	return (draw_end_y);
}

int	get_tex_x(int stripe)
{
	int	tex_x;

	tex_x = (256 * (stripe - (-gm()->raycast.ray_enemey.spt_w / 2
					+ gm()->raycast.ray_enemey.spt_scr_x)) * BLOCK_PIXEL
			/ gm()->raycast.ray_enemey.spt_w) / 256;
	return (tex_x);
}

double	get_tex_y(int y)
{
	int	d;
	int	tex_y;

	d = y * 256 - WIN_HEIGHT * 128 + gm()->raycast.ray_enemey.spt_h * 128;
	tex_y = ((d * BLOCK_PIXEL) / (gm())->raycast.ray_enemey.spt_h) / 256;
	return (tex_y);
}

void	print_enemey_ray(t_enemy *enemy, int stripe)
{
	int	draw_start_y;
	int	draw_end_y;
	int	y;
	int	color;

	draw_start_y = get_draw_start_y();
	draw_end_y = get_draw_end_y();
	y = draw_start_y;
	if (gm()->raycast.ray_enemey.trans_y > 0 && stripe > 0 && stripe < WIN_WIDTH
		&& gm()->raycast.ray_enemey.trans_y < gm()->raycast.z_buffer[stripe])
	{
		while (y < draw_end_y)
		{
			color = get_pixel_color(action_enemy(enemy), get_tex_x(stripe),
					get_tex_y(y));
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(&gm()->image_buffer, stripe, y, color);
			y++;
		}
	}
}
