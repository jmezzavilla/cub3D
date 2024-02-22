/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:24:12 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 19:00:13 by analexan         ###   ########.fr       */
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

// mode 0 = free file, mode 1 = free file and map, mode 2 = free all
void	free_file(t_file *file, int mode)
{
	if (mode)
	{
		free(file->path_ea);
		free(file->path_so);
		free(file->path_we);
		free(file->path_no);
		free(file->color_c);
		free(file->color_f);
		if (mode == 2)
			ft_lstclear(&file->map_lst, clean_lst);
	}
	free(file);
}

/*
> 3
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	ft_cleanup_strs(game->map);
	ft_cleanup_strs(game->map_checker);
> 2
	free(game->scene);
> 1
	mlx_destroy_image(game->mlx, game->image_buffer.img);
	mlx_destroy_image(game->mlx, game->scene->text_no.img);
	mlx_destroy_image(game->mlx, game->scene->text_ea.img);
	mlx_destroy_image(game->mlx, game->scene->text_so.img);
	mlx_destroy_image(game->mlx, game->scene->text_we.img);
	destroy_player(game);
> 0
	free(game->raycast.map);
	free(game->raycast.side_dist);
	free(game->raycast.delta_dist);
	free(game->raycast.dir);
	free_file(game->file, 2);
> -1
	free(game->mlx);
*/
void	destroy_game(t_game *game)
{
	mlx_do_key_autorepeaton(gm()->mlx);
	free_file(game->file, 2);
	free(game->raycast.map);
	free(game->raycast.side_dist);
	free(game->raycast.delta_dist);
	free(game->raycast.dir);
	destroy_player(game);
	mlx_destroy_image(game->mlx, game->image_buffer.img);
	mlx_destroy_image(game->mlx, game->scene->text_no.img);
	mlx_destroy_image(game->mlx, game->scene->text_ea.img);
	mlx_destroy_image(game->mlx, game->scene->text_so.img);
	mlx_destroy_image(game->mlx, game->scene->text_we.img);
	free(game->scene);
	ft_cleanup_strs(game->map);
	ft_cleanup_strs(game->map_checker);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	end_game(int mode)
{
	(void)mode;
	if (gm() && gm()->file)
		destroy_game(gm());
	exit(EXIT_SUCCESS);
}
