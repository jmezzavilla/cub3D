/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:24:12 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 16:01:25 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_lst(void *item)
{
	if (item)
		free(item);
}

void	destroy_player(t_game *game)
{
	free(game->player->dir);
	free(game->player->plane);
	free(game->player->pos);
	free(game->player);
}

void	destroy_game(t_game *game)
{
	mlx_do_key_autorepeaton(gm()->mlx);
	mlx_destroy_image(game->mlx, game->image_buffer.img);
	mlx_destroy_image(game->mlx, game->scene->text_no.img);
	mlx_destroy_image(game->mlx, game->scene->text_ea.img);
	mlx_destroy_image(game->mlx, game->scene->text_so.img);
	mlx_destroy_image(game->mlx, game->scene->text_we.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	ft_lstclear(&game->file->map_lst, clean_lst);
	ft_cleanup_strs(game->map);
	ft_cleanup_strs(game->map_checker);
	destroy_player(game);
	free(game->file->path_ea);
	free(game->file->path_so);
	free(game->file->path_we);
	free(game->file->path_no);
	free(game->file->color_c);
	free(game->file->color_f);
	free(game->scene);
	free(game->file);
	free(game->raycast.map);
	free(game->raycast.side_dist);
	free(game->raycast.delta_dist);
	free(game->raycast.dir);
	free(game->mlx);
}

void	end_game(void)
{
	if (gm() && gm()->file)
		destroy_game(gm());
	exit(EXIT_SUCCESS);
}
