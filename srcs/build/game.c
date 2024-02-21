/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:10 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 23:42:10 by jealves-         ###   ########.fr       */
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
	game->image_buffer.img = mlx_new_image(game->mlx, width, height);
	game->image_buffer.addr = mlx_get_data_addr(game->image_buffer.img,
			&game->image_buffer.bits_per_pixel, &game->image_buffer.line_length,
			&game->image_buffer.endian);
	game->image_buffer.width = width;
	game->image_buffer.height = height;
}

void	build_game(void)
{
	(gm()->raycast.map) = set_coord((double)0, (double)0);
	(gm()->raycast.side_dist) = set_coord((double)0, (double)0);
	(gm()->raycast.delta_dist) = set_coord((double)0, (double)0);
	(gm()->raycast.dir) = set_coord((double)0, (double)0);
	(gm()->controls.minimap_view) = false;
}
//necessario o check ser antes do build_mlx e apos o build_player, 
//pois no check verificamos as estruturas criadas pelas 4 funções acima.
//e caso tenha problema nem chega a abrir a tela preta.
void	build(char *map_path)
{
	build_file(map_path);
	build_game();
	search_player();
	check();
	build_mlx_itens(gm());
	build_scene();
}
