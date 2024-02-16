/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:10 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/03 19:12:53 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	build_mlx_itens(t_game *game)
{
	int	width;
	int	height;

	width = 1600;
	height = 900;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, width, height, "cub3D");
	game->image_b.img = mlx_new_image(game->mlx, width, height);
	game->image_b.addr = mlx_get_data_addr(game->image_b.img,
			&game->image_b.bits_per_pixel,
			&game->image_b.line_length, &game->image_b.endian);
	game->image_b.width = width;
	game->image_b.height = height;
}

void	build_game(void)
{
	gm()->nbr_player = 0;
}

void	build(char *map_path)
{
	build_file(map_path);
	build_game();
	build_characters();
	build_mlx_itens(gm());
	build_sprites();
	check();
}
