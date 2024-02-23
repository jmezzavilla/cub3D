/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:06:57 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/22 23:58:01 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	// Calculate height of line to draw on screen
	if (game->raycast.perp_wall_dist > 0)...
	// calculate lowest and highest pixel to fill in current stripe
	draw_start = -game->raycast.line_height / 2 + WIN_HEIGHT / 2;...
*/
void	draw_raycast(int x, t_game *game, t_door *door)
{
	int	draw_start;
	int	draw_end;

	if (game->raycast.perp_wall_dist > 0)
		game->raycast.line_height = (int)(WIN_HEIGHT
				/ game->raycast.perp_wall_dist);
	else
		game->raycast.line_height = (int)WIN_HEIGHT;
	draw_start = -game->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_start > WIN_HEIGHT)
		draw_start = WIN_HEIGHT - 1;
	draw_end = game->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	if (draw_end < 0)
		draw_end = 0;
	draw_wall(x, draw_start, draw_end, door);
	paint_floor(game->scene->color_f, x, draw_end, game);
	paint_ceiling(game->scene->color_c, x, draw_start, game);
}

// this calculates the distance from the starting
// point to the first line in the grid
// if (game->raycast.dir->x < 0)...
void	calc_steps(t_game *game)
{
	if (game->raycast.dir->x < 0)
	{
		game->raycast.step_x = -1;
		game->raycast.side_dist->x = ((game->player->pos->x)
				- game->raycast.map->x) * game->raycast.delta_dist->x;
	}
	else
	{
		game->raycast.step_x = 1;
		game->raycast.side_dist->x = (game->raycast.map->x + 1
				- (game->player->pos->x)) * game->raycast.delta_dist->x;
	}
	if (game->raycast.dir->y < 0)
	{
		game->raycast.step_y = -1;
		game->raycast.side_dist->y = ((game->player->pos->y)
				- game->raycast.map->y) * game->raycast.delta_dist->y;
	}
	else
	{
		game->raycast.step_y = 1;
		game->raycast.side_dist->y = (game->raycast.map->y + 1
				- (game->player->pos->y)) * game->raycast.delta_dist->y;
	}
}

//! This is done by repeatedly adding the distance the ray
//! travels in the x or y direction to the current
//! position of the ray, and checking whether the new
//! position is a wall.
// game->raycast.side_dist->x += game->raycast.delta_dist->x;...
t_door	*dda(t_game *game)
{
	int		hit;
	char	c;

	hit = 0;
	while (hit == 0)
	{
		if (game->raycast.side_dist->x < game->raycast.side_dist->y)
		{
			game->raycast.side_dist->x += game->raycast.delta_dist->x;
			game->raycast.map->x += game->raycast.step_x;
			game->raycast.side = 0;
		}
		else
		{
			game->raycast.side_dist->y += game->raycast.delta_dist->y;
			game->raycast.map->y += game->raycast.step_y;
			game->raycast.side = 1;
		}
		c = game->map[(int)game->raycast.map->y][(int)game->raycast.map->x];
		if (game->raycast.map->x >= 0 && game->raycast.map->x < WIN_WIDTH
			&& game->raycast.map->y >= 0 && game->raycast.map->y < WIN_HEIGHT
			&& (c == '1' || c == 'D'))
			hit = 1;
	}
	return (get_door((int)game->raycast.map->y, (int)game->raycast.map->x));
}

/*
	// x is for each column of the screen (0 to 1600)
	// x / (double)WIN_WIDTH is a num from 0 to 1 that
	// represents a num from 0 to 1600
	// and then the (2 *) and the (-1) are to convert the scale 0 to 1 ->
		-1 to 1
	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	//! game->player->plane->x is from -1 to 1
	// this operation is to calculate the point here the ray is pointing
	game->raycast.dir->x = game->player->dir->x + game->player->plane->x...
	/// the division through zero is avoided by setting it to a very high value:
	/// 1e30 is an arbitrarily chosen high enough number
	/// deltaDist is the length of ray from one x or y-side to next x or y-side
	if (game->raycast.dir->x == 0)...
*/
void	init_ray(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	game->raycast.dir->x = game->player->dir->x + game->player->plane->x
		* camera_x;
	game->raycast.dir->y = game->player->dir->y + game->player->plane->y
		* camera_x;
	game->raycast.map->x = (int)game->player->pos->x;
	game->raycast.map->y = (int)game->player->pos->y;
	if (game->raycast.dir->x == 0)
		game->raycast.delta_dist->x = 1e30;
	else
		game->raycast.delta_dist->x = fabs(1 / game->raycast.dir->x);
	if (game->raycast.dir->y == 0)
		game->raycast.delta_dist->y = 1e30;
	else
		game->raycast.delta_dist->y = fabs(1 / game->raycast.dir->y);
}

//! raycast.side_dist are the distances that the ray
//! has traveled in the x or y directions
// if (game->raycast.side == 0)...
void	raycast(t_game *game)
{
	int		x;
	t_door	*door;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, x);
		calc_steps(game);
		door = dda(game);
		if (game->raycast.side == 0)
			game->raycast.perp_wall_dist = (game->raycast.side_dist->x
					- game->raycast.delta_dist->x);
		else
			game->raycast.perp_wall_dist = (game->raycast.side_dist->y
					- game->raycast.delta_dist->y);
		draw_raycast(x, game, door);
		x++;
	}
}
