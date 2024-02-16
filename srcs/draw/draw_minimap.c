/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:00:10 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/02 21:38:42 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *game)
{
	int	y;
	int	x;
	int	size_y;
	int	size_x;

	y = 0;
	size_y = ft_strlen_matrix(game->map);
	while (y < size_y)
	{
		x = 0;
		size_x = ft_strlen(game->map[y]);
		while (x < size_x)
		{
			if (game->map[y][x] == '1')
				draw(x * MINIMAP_PX, y * MINIMAP_PX,
					&game->sprites->minimap_wall, game);
			else if (game->map[y][x] != '1' && game->map[y][x] != ' '
				&& game->map[y][x] != '\n')
				draw(x * MINIMAP_PX, y * MINIMAP_PX,
					&game->sprites->minimap_floor, game);
			x++;
		}
		y++;
	}
}
