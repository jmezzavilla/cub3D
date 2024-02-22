/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:44 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 23:39:46 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(char **map, t_coord *pos)
{
	int	y;
	int	x;

	y = pos->y - WALL_DISTANCE;
	x = pos->x - WALL_DISTANCE;
	if (map[y][x] == '1')
		return (true);
	y = pos->y - WALL_DISTANCE;
	x = pos->x + WALL_DISTANCE;
	if (map[y][x] == '1')
		return (true);
	y = pos->y + WALL_DISTANCE;
	x = pos->x - WALL_DISTANCE;
	if (map[y][x] == '1')
		return (true);
	y = pos->y + WALL_DISTANCE;
	x = pos->x + WALL_DISTANCE;
	if (map[y][x] == '1')
		return (true);
	return (false);
}

void	check_colision(char **map, double x, double y, t_coord *pos)
{
	double	temp;

	if (!is_wall(map, pos))
		return ;
	temp = pos->x;
	pos->x = x;
	if (!is_wall(map, pos))
		return ;
	pos->y = y;
	pos->x = temp;
	if (!is_wall(map, pos))
		return ;
	pos->x = x;
	pos->y = y;
}
