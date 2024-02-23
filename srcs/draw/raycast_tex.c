/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:50:36 by analexan          #+#    #+#             */
/*   Updated: 2024/02/23 16:22:52 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// floor makes 3.4 = 3
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

t_buffer	*get_texture_wall(t_game *game, t_door *door)
{
	if (door)
		return (action_door(door));
	else if (game->raycast.side == 0)
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

/*
wall_x = calculates the x-coordinate of the hit point on the wall
tex.x = the x-coordinate of the texture pixel.
step = how much to increase the texture coordinate per screen pixel
the step size is the ratio of the texture height to the wall slice height
tex_pos = initial texture position

Cast the texture coordinate to integer,
and protect with (texHeight - 1) in case of overflow
		tex.y = (int)tex_pos & (BLOCK_PIXEL - 1);
*/
void	draw_wall(int x, int draw_start, int draw_end, t_door *door)
{
	int		i;
	double	wall_x;
	t_coord	tex;
	double	step;
	double	tex_pos;

	i = draw_start;
	wall_x = get_wall_x(gm());
	tex.x = (int)(wall_x * BLOCK_PIXEL);
	if (gm()->raycast.side == 0 && gm()->raycast.dir->x > 0)
		tex.x = BLOCK_PIXEL - tex.x - 1;
	if (gm()->raycast.side == 1 && gm()->raycast.dir->y < 0)
		tex.x = BLOCK_PIXEL - tex.x - 1;
	step = 1.0 * BLOCK_PIXEL / gm()->raycast.line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + gm()->raycast.line_height / 2)
		* step;
	while (i < draw_end)
	{
		tex.y = (int)tex_pos & (BLOCK_PIXEL - 1);
		tex_pos += step;
		put_pixel(&gm()->image_buffer, x, i,
			get_pixel_color(get_texture_wall(gm(), door), tex.x, tex.y));
		i++;
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
