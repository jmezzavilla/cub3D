/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:58:51 by analexan          #+#    #+#             */
/*   Updated: 2024/02/16 16:50:46 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char worldMap[8][8] =
{
  {'1','1','1','1','1','1','1','1'},
  {'1','0','0','0','0','0','0','1'},
  {'1','0','1','0','0','0','0','1'},
  {'1','0','0','0','0','1','0','1'},
  {'1','0','0','0','0','1','0','1'},
  {'1','0','0','0','0','1','0','1'},
  {'1','0','0','0','0','0','0','1'},
  {'1','1','1','1','1','1','1','1'}
};

void	draw_frame(void)
{
	char	str[50];
	int	x;
	int	y = -1;
	put_square(&gm()->image_buffer, 0, 0, gm()->win_size.x - 1, gm()->win_size.y - 1, 0, 0);
	while (++y < 8)
	// while (++y < gm()->map_size.y)
	{
		x = -1;
		while (++x < 8)
		// while (++x < gm()->map_size.x)
		{
			put_square(&gm()->image_buffer, x * blockSize, y * blockSize,
				x * blockSize + blockSize - 1, y * blockSize + blockSize - 1, worldMap[y][x] == '1', argb(0, 64, 64, 64));
				// x * blockSize + blockSize - 1, y * blockSize + blockSize - 1, gm()->map[y][x] == '1', argb(0, 64, 64, 64));
		}
	}

	float xx = blockSize * cos(gm()->angle);
	float yy = blockSize * sin(gm()->angle);
	put_line(&gm()->image_buffer, gm()->pos.x + blockSize / 4, gm()->pos.y + blockSize / 4,
		gm()->pos.x + xx + blockSize / 4, gm()->pos.y + yy + blockSize / 4, 0x004895EF);
	put_square(&gm()->image_buffer, gm()->pos.x + 7, gm()->pos.y + 7, gm()->pos.x + 5 - 1 + 7, gm()->pos.y + 5 - 1 + 7, 0, argb(0, 255, 0, 0));
	mlx_put_image_to_window(gm()->mlx, gm()->win, gm()->image_buffer.img, 0, 0);

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

// if '\n' is found, it will be counted for the length
void get_map_length(void)
{
	int	i;

	i = -1;
	while (gm()->map[++i])
		if (gm()->map_size.x < ft_strlen(gm()->map[i]))
			gm()->map_size.x = ft_strlen(gm()->map[i]);
	gm()->map_size.y = i;
}

void	cub3d_init(void)
{
	// get_map_length();
	gm()->angle = -M_PI_2;
	gm()->map_size.x = 8;
	gm()->map_size.y = 8;
	gm()->win_size.x = gm()->map_size.x * blockSize;
	gm()->win_size.y = gm()->map_size.y * blockSize;
	gm()->pos.x = gm()->win_size.x / 2 - blockSize / 4;
	gm()->pos.y = gm()->win_size.y / 2 - blockSize / 4;
	gm()->mlx = mlx_init();
	gm()->win = mlx_new_window(gm()->mlx, gm()->win_size.x, gm()->win_size.y, "cub3D");
	create_image(gm()->win_size.x, gm()->win_size.y, 25, &gm()->image_buffer);
}
