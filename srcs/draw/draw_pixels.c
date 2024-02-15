/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:27:08 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/03 19:14:43 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_buffer *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		error_msg("Pixel");
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_buffer *sprite, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= sprite->width || y >= sprite->height)
		return (0);
	dst = sprite->addr + (y * sprite->line_length + x * (sprite->bits_per_pixel
				/ 8));
	return (*(unsigned int *)dst);
}

void	draw(int x, int y, t_buffer *sprite, t_game *game)
{
	int	sprite_x;
	int	sprite_y;
	int	color;

	sprite_x = 0;
	sprite_y = 0;
	while (sprite_y < sprite->height)
	{
		sprite_x = 0;
		while (sprite_x < sprite->width)
		{
			color = get_pixel_color(sprite, sprite_x, sprite_y);
			put_pixel(&game->image_b, x + sprite_x, y + sprite_y, color);
			sprite_x++;
		}
		sprite_y++;
	}
}
