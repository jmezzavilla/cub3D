/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:54:40 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/26 12:27:15 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(t_game *game)
{
	event_player(game);
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image_buffer.img, 0, 0);
	return (EXIT_SUCCESS);
}

int	key_press(int key, t_game *game)
{
	if (key == W_KEY)
		game->controls.up = W_KEY;
	else if (key == S_KEY)
		game->controls.down = S_KEY;
	else if (key == A_KEY)
		game->controls.left = A_KEY;
	else if (key == D_KEY)
		game->controls.right = D_KEY;
	else if (key == LEFT_KEY)
		game->controls.rotate_left = LEFT_KEY;
	else if (key == RIGHT_KEY)
		game->controls.rotate_right = RIGHT_KEY;
	else if (key == M_KEY)
		game->controls.minimap_view = !game->controls.minimap_view;
	else if (key == SPACE_KEY)
		open_door(game->player);
	else if (key == ESC_KEY)
		return (quit());
	return (EXIT_SUCCESS);
}

int	key_release(int key, t_game *game)
{
	if (key == W_KEY)
		game->controls.up = -1;
	else if (key == S_KEY)
		game->controls.down = -1;
	else if (key == A_KEY)
		game->controls.left = -1;
	else if (key == D_KEY)
		game->controls.right = -1;
	else if (key == LEFT_KEY)
		game->controls.rotate_left = -1;
	else if (key == RIGHT_KEY)
		game->controls.rotate_right = -1;
	return (EXIT_SUCCESS);
}

int	quit(void)
{
	prt("\033[1;34mExit\033[0m\n");
	free_game(gm());
	exit(EXIT_SUCCESS);
	return (0);
}

void	hook(void)
{
	gm()->mouse_on = 1;
	mlx_do_key_autorepeatoff(gm()->mlx);
	mlx_mouse_hook(gm()->win, mouse_click, gm());
	mlx_hook(gm()->win, 6, 1L << 6, mouse_move, gm());
	mlx_hook(gm()->win, KeyPress, KeyPressMask, key_press, gm());
	mlx_hook(gm()->win, KeyRelease, KeyReleaseMask, key_release, gm());
	mlx_hook(gm()->win, 17, 0, quit, gm());
	mlx_loop_hook(gm()->mlx, loop, gm());
	mlx_loop(gm()->mlx);
}
