/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:54:40 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 12:19:04 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(t_game *game)
{
	clear_screen();
	event_player(game);
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image_buffer.img, 0, 0);
	return (EXIT_SUCCESS);
}

int	key_press(int key, t_game *data)
{
	if (key == W_KEY)
		data->controls.up = W_KEY;
	else if (key == S_KEY)
		data->controls.down = S_KEY;
	else if (key == A_KEY)
		data->controls.left = A_KEY;
	else if (key == D_KEY)
		data->controls.right = D_KEY;
	else if (key == LEFT_KEY)
		data->controls.rotate_left = LEFT_KEY;
	else if (key == RIGHT_KEY)
		data->controls.rotate_right = RIGHT_KEY;
	else if (key == ESC_KEY)
		return (quit());
	return (EXIT_SUCCESS);
}

int	key_release(int key, t_game *data)
{
	if (key == W_KEY)
		data->controls.up = -1;
	else if (key == S_KEY)
		data->controls.down = -1;
	else if (key == A_KEY)
		data->controls.left = -1;
	else if (key == D_KEY)
		data->controls.right = -1;
	else if (key == LEFT_KEY)
		data->controls.rotate_left = -1;
	else if (key == RIGHT_KEY)
		data->controls.rotate_right = -1;
	return (EXIT_SUCCESS);
}

int	quit(void)
{
	prt("Fim\n");
	end_game();
	return (0);
}

void	hook(void)
{
	mlx_do_key_autorepeatoff(gm()->mlx);
	mlx_hook(gm()->win, KeyPress, KeyPressMask, key_press, gm());
	mlx_hook(gm()->win, KeyRelease, KeyReleaseMask, key_release, gm());
	mlx_hook(gm()->win, 17, 0, quit, &gm);
	mlx_loop_hook(gm()->mlx, loop, gm());
	mlx_loop(gm()->mlx);
}
