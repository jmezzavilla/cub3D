/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:00:10 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/06 21:56:19 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_25px(t_buffer *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_PX)
	{
		j = 0;
		while (j < MINIMAP_PX)
		{
			put_pixel(img, (x * MINIMAP_PX) + i, (y * MINIMAP_PX) + j, color);
			j++;
		}
		i++;
	}
}
int	get_color(char c)
{
	int	color;

	if (c == '0')
		color = 0xf0f8ff;
	else if (c == '2')
		color = 0x00FF00;
	else if (c == '1' || c == '3')
		color = 0x1E90FF;
	else
		color = 0;
	return (color);
}
void	draw_player(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_PX / 2)
	{
		j = -1;
		while (j < MINIMAP_PX / 2)
		{
			put_pixel(&data->image_buffer, (data->player->pos->x * MINIMAP_PX) + i,
				(data->player->pos->y * MINIMAP_PX ) + j, 0xDC143C);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	size_y;
	int	size_x;
	int	color;

	y = 0;
	size_y = ft_strlen_matrix(game->map);
	while (y < size_y)
	{
		x = 0;
		size_x = ft_strlen(game->map[y]);
		while (x < size_x)
		{
			color = get_color(game->map[y][x]);
			if (color)
				draw_25px(&game->image_buffer, x, y, color);
			x++;
		}
		y++;
	}
	draw_player(game);
}
