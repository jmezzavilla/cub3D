/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:31 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/27 13:21:33 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill(int y, int x, char **map, int size_y)
{
	int	size_x;

	size_x = ft_strlen(map[y]);
	if (y >= size_y || x >= size_x || map[y][x] == '\0' || map[y][x] == '\n'
		|| map[y][x] == ' ' || map[y][x] == '1' || map[y][x] == 'I'
		|| map[y][x] == 'V' || y < 0 || x < 0)
		return ;
	if (is_map_char(map, y + 1, x - 1) && is_map_char(map, y, x - 1)
		&& is_map_char(map, y - 1, x - 1) && is_map_char(map, y + 1, x + 1)
		&& is_map_char(map, y, x + 1) && is_map_char(map, y - 1, x + 1)
		&& is_map_char(map, y + 1, x) && is_map_char(map, y - 1, x))
		map[y][x] = 'V';
	else
		map[y][x] = 'I';
	fill(y + 1, x, map, size_y);
	fill(y, x + 1, map, size_y);
	fill(y - 1, x, map, size_y);
	fill(y, x - 1, map, size_y);
}

void	check_floodfill(char **map)
{
	int	x;
	int	size_x;
	int	y;
	int	size_y;

	y = 0;
	size_y = ft_strlen_matrix(map);
	while (y < size_y)
	{
		x = 0;
		size_x = ft_strlen(map[y]);
		while (x < size_x)
		{
			if (map[y][x] == 'I')
				error_msg("Invalid map structure");
			x++;
		}
		y++;
	}
}

void	floodfill(char **map)
{
	int	x;
	int	size_x;
	int	y;
	int	size_y;

	y = 0;
	size_y = ft_strlen_matrix(map);
	while (y < size_y)
	{
		x = 0;
		size_x = ft_strlen(map[y]);
		while (x < size_x)
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				fill(y, x, map, size_y);
			x++;
		}
		y++;
	}
	check_floodfill(map);
}
