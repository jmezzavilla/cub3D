/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:44 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/22 14:56:51 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This function checks if the new position is a wall
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

/*
This function checks if moving to a new position would result in a collision
with a wall by checking the new position horizontally and vertically.
If the new position is valid, it updates the current position to the new position
*/
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
