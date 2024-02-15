/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:54:40 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/15 16:56:18 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(t_game *game)
{
	int	width;
	int	height;

	width = 1600;
	height = 900;
	game->image_buffer.img = mlx_new_image(game->mlx, width, height);
	game->image_buffer.addr = mlx_get_data_addr(game->image_buffer.img,
			&game->image_buffer.bits_per_pixel, &game->image_buffer.line_length,
			&game->image_buffer.endian);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image_buffer.img, 0, 0);
	mlx_destroy_image(game->mlx, game->image_buffer.img);
	return (EXIT_SUCCESS);
}

int	keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		return (quit());
	if (keycode == LETTER_KEY_UP)
		game->player->pos->y = game->player->pos->y - 0.039;
	if (keycode == LETTER_KEY_DOWN)
		game->player->pos->y = game->player->pos->y + 0.039;
	if (keycode == LETTER_KEY_LEFT)
		game->player->pos->x = game->player->pos->x - 0.039;
	if (keycode == LETTER_KEY_RIGHT)
		game->player->pos->x = game->player->pos->x + 0.039;
	return (0);
}

int quit(void)
{
	prt("Fim\n");
	mlx_destroy_image(gm()->mlx, gm()->image_b.img);
	mlx_destroy_window(gm()->mlx, gm()->win);
	mlx_destroy_display(gm()->mlx);
	free(gm()->mlx);
	exit(0);
}

void	hook(void)
{
	mlx_hook(gm()->win, KeyPress, KeyPressMask, keypress, NULL);
	mlx_hook(gm()->win, 17, 0, quit, &gm);
	//mlx_hook(gm()->window, 17, 0, closing_game, gm());
	mlx_loop_hook(gm()->mlx, loop, gm());
	mlx_loop(gm()->mlx);
}
