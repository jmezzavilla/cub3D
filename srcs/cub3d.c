/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:51 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/06 13:15:32 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*gm(void)
{
	static t_game	game;

	return (&game);
}

int	cub3d(char *map_path)
{
	build(map_path);
	hook();
	return (1);
}
#define mapWidth 8
#define mapHeight 8
#define screenWidth 640
#define screenHeight 480

char	worldMap[mapWidth][mapHeight] = {{'1', '1', '1', '1', '1', '1', '1', 0},
		{'1', '0', '0', '0', '0', '0', '1', 0}, {'1', '0', '0', '0', '0', '0',
		'1', 0}, {'1', '0', '0', '0', '0', '0', '1', 0}, {'1', '0', '0', '0',
		'0', '0', '1', 0}, {'1', '0', '0', '0', '0', '0', '1', 0}, {'1', '1',
		'1', '1', '1', '1', '1', 0}};
/*int quit(void)
{
	int	height;

	// (void)game;
	mlx_destroy_image(gm()->mlx, gm()->image_buffer.img);
	mlx_destroy_window(gm()->mlx, gm()->win);
	mlx_destroy_display(gm()->mlx);
	free(gm()->mlx);
	exit(0);
}*/
int	main(int ac, char **av)
// int	main(void)
{
	/*int	width;
	width = 500;
	height = 500;
	gm()->mlx = mlx_init();
	gm()->win = mlx_new_window(gm()->mlx, width, height, "cub3D");
	gm()->image_buffer.img = mlx_new_image(gm()->mlx, width, height);
	// int	x;
	// int	y;
	// y = 0;
	// while (y < mapHeight)
	// {
	// 	x = 0;
	// 	printf("wm: %s", worldMap[y]);
	// 	// while (x < mapWidth)
	// 	// {
	// 	// 	printf("wm: %c", worldMap[x][y]);
	// 	// 	// if (worldMap[y][x] == 'N' || worldMap[y][x] == 'S'
	// 	// 	// 	|| worldMap[y][x] == 'E' || worldMap[y][x] == 'W')
	// 	// 	// 	printf("wm: %c\n", worldMap[x][y]);
	// 	// 	x++;
	// 	// }
	// 	printf("\n");
	// 	y++;
	// }
	mlx_hook(gm()->win, 17, 0, quit, &gm);
	mlx_loop(gm()->mlx);
	return (0);*/
	if (ac == 2)
		return (cub3d(av[1]));
	else
		error_msg("Invalid Number of Arguments");
}
