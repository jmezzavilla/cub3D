/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:06:57 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 23:47:55 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_x(t_game *game)
{
	double	wall_x;

	if (game->raycast.side == 0)
		wall_x = (game->player->pos->y) + game->raycast.perp_wall_dist
			* game->raycast.dir->y;
	else
		wall_x = (game->player->pos->x) + game->raycast.perp_wall_dist
			* game->raycast.dir->x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

t_buffer	*get_texture_wall(t_game *game)
{
	if (game->raycast.side == 0)
	{
		if (game->raycast.dir->x > 0)
			return (&game->scene->text_ea);
		else
			return (&game->scene->text_we);
	}
	else
	{
		if (game->raycast.dir->y > 0)
			return (&game->scene->text_so);
		else
			return (&game->scene->text_no);
	}
	return (NULL);
}

void	draw_wall(int x, int draw_start, int draw_end, t_game *game)
{
	int		i;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;

	i = draw_start;
	// texturing calculations
	// int texNum = worldMap[map_x][map_y] - 1;
		//1 subtracted from it so that texture 0 can be used!
	// calculate value of wall_x
	wall_x = get_wall_x(game); // where exactly the wall was hit
	// x coordinate on the texture
	tex_x = (int)(wall_x * BLOCK_PIXEL);
	if (game->raycast.side == 0 && game->raycast.dir->x > 0)
		tex_x = BLOCK_PIXEL - tex_x - 1;
	if (game->raycast.side == 1 && game->raycast.dir->y < 0)
		tex_x = BLOCK_PIXEL - tex_x - 1;
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * BLOCK_PIXEL / game->raycast.line_height;
	// Starting texture coordinate
	tex_pos = (draw_start - WIN_HEIGHT / 2 + game->raycast.line_height / 2)
		* step;
	while (i < draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		tex_y = (int)tex_pos & (BLOCK_PIXEL - 1);
		tex_pos += step;
		put_pixel(&game->image_buffer, x, i,
			get_pixel_color(get_texture_wall(game), tex_x, tex_y));
		i++;
		// if (0 == i % 10)
		// 	mlx_put_image_to_window(game->mlx, game->win, game->image_buffer.img, 0, 0);
	}
}

void	paint_floor(int color, int x, int d_end, t_game *game)
{
	int	i;

	i = d_end;
	if (d_end >= WIN_HEIGHT)
		return ;
	while (i < WIN_HEIGHT)
	{
		put_pixel(&game->image_buffer, x, i, color);
		i++;
	}
}

void	paint_ceiling(int color, int x, int d_start, t_game *game)
{
	int	i;

	i = 0;
	if (d_start <= 0)
		return ;
	while (i < d_start)
	{
		put_pixel(&game->image_buffer, x, i, color);
		i++;
	}
}
void	draw_raycast(int x, t_game *game)
{
	int	draw_start;
	int	draw_end;

	// Calculate height of line to draw on screen
	if (game->raycast.perp_wall_dist > 0)
		game->raycast.line_height = (int)(WIN_HEIGHT
				/ game->raycast.perp_wall_dist);
	else
		game->raycast.line_height = (int)WIN_HEIGHT;
	// calculate lowest and highest pixel to fill in current stripe
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
	draw_wall(x, draw_start, draw_end, game);
	paint_floor(game->scene->color_f.code_rgb, x, draw_end, game);
	paint_ceiling(game->scene->color_c.code_rgb, x, draw_start, game);
}

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
	/*
	//calculate step and initial side_dist
		if (ray_dir_x < 0)
		{
		step_x = -1;
		side_dist_x = (posX - map_x) * delta_dist_x;
		}
		else
		{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - posX) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
		step_y = -1;
		side_dist_y = (posY - map_y) * delta_dist_y;
		}
		else
		{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - posY) * delta_dist_y;
		}
	*/
}

void	dda(t_game *game)
{
	int hit = 0; // was there a wall hit?
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
		if (game->raycast.map->x >= 0 && game->raycast.map->x < WIN_WIDTH
			&& game->raycast.map->y >= 0 && game->raycast.map->y < WIN_HEIGHT
			&& game->map[(int)game->raycast.map->y][(int)game->raycast.map->x] == '1')
			hit = 1;
	}
	/*
	int hit = 0; //was there a wall hit?
	//perform DDA
		while (hit == 0)
		{
		//jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (worldMap[map_x][map_y] > 0) hit = 1;
		}
		*/
}

void	init_ray(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	game->raycast.dir->x = game->player->dir->x + game->player->plane->x
		* camera_x;
	game->raycast.dir->y = game->player->dir->y + game->player->plane->y
		* camera_x;
	/*
	//calculate ray position and direction
		double camera_x = 2 * x / double(w) - 1; //x-coordinate in camera space
		ray_dir_x = dirX + planeX * camera_x;
		ray_dir_y = dirY + planeY * camera_x;
	*/
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
	/* game->raycast.hit = 0;
		//which box of the map we're in
	map_x = int(posX);
	map_y = int(posY);
	//length of ray from current position to next x or y-side
	//length of ray from one x or y-side to next x or y-side
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : std::abs(1 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : std::abs(1 / ray_dir_y);
	//what direction to step in x or y-direction (either +1 or -1)
	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	*/
}

void	raycast(t_game *game)
{
	int x = 0;

	while (x < WIN_WIDTH)
	{
		init_ray(game, x);
		calc_steps(game);
		dda(game);
		if (game->raycast.side == 0)
			game->raycast.perp_wall_dist = (game->raycast.side_dist->x
					- game->raycast.delta_dist->x);
		else
			game->raycast.perp_wall_dist = (game->raycast.side_dist->y
					- game->raycast.delta_dist->y);
		/*//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0) perp_wall_dist = (side_dist_x - delta_dist_x);
		else          perp_wall_dist = (side_dist_y - delta_dist_y);
		*/
		draw_raycast(x, game);
		x++;
	}
}

