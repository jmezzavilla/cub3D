/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:54:40 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/16 20:47:02 by jealves-         ###   ########.fr       */
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

int	keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		return (quit());
	if (keycode == W_KEY)
		game->player->pos->y = game->player->pos->y - 0.039;
	if (keycode == S_KEY)
		game->player->pos->y = game->player->pos->y + 0.039;
	if (keycode == A_KEY)
		game->player->pos->x = game->player->pos->x - 0.039;
	if (keycode == D_KEY)
		game->player->pos->x = game->player->pos->x + 0.039;
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
