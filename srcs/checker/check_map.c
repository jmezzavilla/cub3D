/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:17 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/22 17:15:12 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_first_last_line(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[0][x])
	{
		if (map[0][x] != '1' && map[0][x] != ' ' && map[0][x] != '\n')
			error_msg("Invalid map");
		x++;
	}
	x = 0;
	y = ft_strlen_matrix(map) - 1;
	while (map[y][x])
	{
		if (map[y][x] != '1' && map[y][x] != ' ' && map[y][x] != '\n')
			error_msg("Invalid map");
		x++;
	}
}

void	check_first_column(char **map, int y)
{
	int	x;

	x = 0;
	while (map[y][x])
	{
		if (map[y][x] == ' ')
		{
			x++;
			continue ;
		}
		if (map[y][x] != '1')
			error_msg("Invalid map");
		break ;
	}
}

void	check_last_column(char **map, int y)
{
	int	x;

	x = ft_strlen(map[y]) - 1;
	while (map[y][x])
	{
		if (map[y][x] == ' ' || map[y][x] == '\n')
		{
			x--;
			continue ;
		}
		if (map[y][x] != '1')
			error_msg("Invalid map");
		break ;
	}
}

void	check_middle_line(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		check_first_column(map, y);
		check_last_column(map, y);
		y++;
	}
}

void	check_map(void)
{
	check_first_last_line(gm()->map);
	check_middle_line(gm()->map);
	floodfill(gm()->map_checker);
}
