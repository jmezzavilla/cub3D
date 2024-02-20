/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:54:40 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 13:56:24 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	clear_screen(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (gm()->map[y])
	{
		x = 0;
		while (gm()->map[y][x])
		{
			put_pixel(&gm()->image_buffer, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	loop(t_game *game)
{
	clear_screen();
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image_buffer.img, 0, 0);
	return (EXIT_SUCCESS);
}
double walkSpeed = 0.039;

int	keypress(int keycode, t_game *game)
{
	double rotSpeed = 0.01 * 3.0; 
	if (keycode == ESC_KEY)
		return (quit());
	if (keycode == SHIFT_KEY)
	{
		if (walkSpeed == 0.039)
			walkSpeed = 0.15;
		else
			walkSpeed = 0.039;
	}
	// double moveSpeed = 0.01 * 5.0;
	// if (keycode == W_KEY)
	// {
	//   if(game->map[(int)(game->player->pos->x + game->player->dir->x * moveSpeed)][(int)(game->player->pos->y)] == false) game->player->pos->x += game->player->dir->x * moveSpeed;
	//   if(game->map[(int)(game->player->pos->x)][(int)(game->player->pos->y + game->player->dir->y * moveSpeed)] == false) game->player->pos->y += game->player->dir->y * moveSpeed;
	// }
	// if (keycode == S_KEY)
	// {
	//   if(game->map[(int)(game->player->pos->x - game->player->dir->x * moveSpeed)][(int)(game->player->pos->y)] == false) game->player->pos->x -= game->player->dir->x * moveSpeed;
	//   if(game->map[(int)(game->player->pos->x)][(int)(game->player->pos->y - game->player->dir->y * moveSpeed)] == false) game->player->pos->y -= game->player->dir->y * moveSpeed;
	// }
	if (keycode == W_KEY)
		game->player->pos->y -= walkSpeed;
	if (keycode == S_KEY)
		game->player->pos->y += walkSpeed;
	if (keycode == A_KEY)
		game->player->pos->x -= walkSpeed;
	if (keycode == D_KEY)
		game->player->pos->x += walkSpeed;
	if (keycode == LEFT_KEY)
	{
		double oldDirX = game->player->dir->x;
		game->player->dir->x = game->player->dir->x * cos(-rotSpeed) - game->player->dir->y * sin(-rotSpeed);
		game->player->dir->y = oldDirX * sin(-rotSpeed) + game->player->dir->y * cos(-rotSpeed);
		double oldPlaneX = game->player->plane->x;
		game->player->plane->x = game->player->plane->x * cos(-rotSpeed) - game->player->plane->y * sin(-rotSpeed);
		game->player->plane->y = oldPlaneX * sin(-rotSpeed) + game->player->plane->y * cos(-rotSpeed);
	}
	if (keycode == RIGHT_KEY)
	{
		double oldDirX = game->player->dir->x;
		game->player->dir->x = game->player->dir->x * cos(rotSpeed) - game->player->dir->y * sin(rotSpeed);
		game->player->dir->y = oldDirX * sin(rotSpeed) + game->player->dir->y * cos(rotSpeed);
		double oldPlaneX = game->player->plane->x;
		game->player->plane->x = game->player->plane->x * cos(rotSpeed) - game->player->plane->y * sin(rotSpeed);
		game->player->plane->y = oldPlaneX * sin(rotSpeed) + game->player->plane->y * cos(rotSpeed);
	}
	return (0);
}

int quit(void)
{
	prt("Fim\n");
	end_game();
	return(0);
}

void	hook(void)
{
	mlx_hook(gm()->win, KeyPress, KeyPressMask, keypress, gm());
	mlx_hook(gm()->win, 17, 0, quit, &gm);
	//mlx_hook(gm()->window, 17, 0, closing_game, gm());
	mlx_loop_hook(gm()->mlx, loop, gm());
	mlx_loop(gm()->mlx);
}
