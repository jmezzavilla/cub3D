/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:00:10 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 23:39:55 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_buffer *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_PX)
	{
		j = 0;
		while (j < MINIMAP_PX)
		{
			put_pixel(img, (x * MINIMAP_PX) + 2.5 + i, (y * MINIMAP_PX) + 2.5
				+ j, color);
			j++;
		}
		i++;
	}
}

int	get_color(char c)
{
	int	color;

	if (c == ' ')
		color = 0;
	else if (c == '0')
		color = 0xf0f8ff;
	else if (c == '1')
		color = gm()->scene->color_f;
	else
		color = gm()->scene->color_c;
	return (color);
}

void	draw_player(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_PX / 2.5)
	{
		j = 0;
		while (j < MINIMAP_PX / 2.5)
		{
			put_pixel(&data->image_buffer, (data->player->pos->x * MINIMAP_PX)
				+ i, (data->player->pos->y * MINIMAP_PX) + j, get_color('P'));
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
	if (!game->controls.minimap_view)
		return ;
	size_y = ft_strlen_matrix(game->map);
	while (y < size_y)
	{
		x = 0;
		size_x = ft_strlen(game->map[y]);
		while (x < size_x && game->map[y][x] != '\n')
		{
			color = get_color(game->map[y][x]);
			if (color)
				draw_map(&game->image_buffer, x, y, color);
			x++;
		}
		y++;
	}
	draw_player(game);
}
