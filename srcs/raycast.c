/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:58:51 by analexan          #+#    #+#             */
/*   Updated: 2024/02/15 16:44:34 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define mapWidth 8
#define mapHeight 8
#define screenWidth 640
#define screenHeight 480
#define blockSize 40
// char worldMap[mapWidth][mapHeight] =
// {
//   {'1','1','1','1','1','1','1', 0},
//   {'1','0','0','0','0','0','1', 0},
//   {'1','0','0','0','0','0','1', 0},
//   {'1','0','0','0','0','0','1', 0},
//   {'1','0','0','0','0','0','1', 0},
//   {'1','0','0','0','0','0','1', 0},
//   {'1','1','1','1','1','1','1', 0}
// };

void	draw_frame(void)
{
	char	str[50];
	int	x;
	int	y = -1;
	put_square(&gm()->image_b, 0, 0, screenWidth - 1, screenHeight - 1, 0, 0);
	while (++y < screenHeight / blockSize)
	{
		x = -1;
		while (++x < screenWidth / blockSize)
			put_square(&gm()->image_b, x * blockSize, y * blockSize,
				x * blockSize + blockSize - 1, y * blockSize + blockSize - 1, 1, argb(0, 64, 64, 64));
	}
	float xx = 40 * cos(gm()->angle);
	float yy = 40 * sin(gm()->angle);
	put_line(&gm()->image_b, gm()->pos.x + blockSize / 4, gm()->pos.y + blockSize / 4,
		gm()->pos.x + xx + blockSize / 4, gm()->pos.y + yy + blockSize / 4, 0x004895EF);
	put_square(&gm()->image_b, gm()->pos.x, gm()->pos.y, gm()->pos.x + 20 - 1, gm()->pos.y + 20 - 1, 0, argb(0, 255, 0, 0));
	mlx_put_image_to_window(gm()->mlx, gm()->win, gm()->image_b.img, 0, 0);

	sprintf(str, "x: %.1f y: %.1f a: %.1f", gm()->pos.x, gm()->pos.y, gm()->angle);
	mlx_string_put(gm()->mlx, gm()->win, 0, 10, 0x00FFFFFF, str);
}

// x = width, y = height
int	key_hook(int keycode)
{
	int step = 10;
	if (keycode == ESC_KEY || keycode == 'q')
		return (quit());
	if (keycode == W_KEY)
		gm()->pos.y -= step;
	else if (keycode == A_KEY)
		gm()->pos.x -= step;
	else if (keycode == D_KEY)
		gm()->pos.x += step;
	else if (keycode == S_KEY)
		gm()->pos.y += step;
	else if (keycode == LEFT_KEY)
		gm()->angle -= 0.1;
	else if (keycode == RIGHT_KEY)
		gm()->angle += 0.1;
	draw_frame();
	return (0);
}

void	cub3d_init(void)
{
	gm()->angle = -M_PI_2;
	gm()->win_size.x = screenWidth;
	gm()->win_size.y = screenHeight;
	gm()->pos.x = screenWidth / 2 - blockSize / 4;
	gm()->pos.y = screenHeight / 2 - blockSize / 4;
	gm()->mlx = mlx_init();
	gm()->win = mlx_new_window(gm()->mlx, gm()->win_size.x, gm()->win_size.y, "cub3D");
	create_image(screenWidth, screenHeight, 25, &gm()->image_b);
}
