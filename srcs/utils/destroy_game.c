/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:24:12 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/22 16:41:27 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_lst(void *item)
{
	if (item)
		free(item);
}

void	destroy_scene_and_player(t_game *gm)
{
	if (gm->scene)
	{
		if (gm->scene->text_no.img)
			mlx_destroy_image(gm->mlx, gm->scene->text_no.img);
		if (gm->scene->text_so.img)
			mlx_destroy_image(gm->mlx, gm->scene->text_so.img);
		if (gm->scene->text_we.img)
			mlx_destroy_image(gm->mlx, gm->scene->text_we.img);
		if (gm->scene->text_ea.img)
			mlx_destroy_image(gm->mlx, gm->scene->text_ea.img);
		free(gm->scene);
	}
	if (!gm->player)
		return ;
	free(gm->player->dir);
	free(gm->player->plane);
	free(gm->player->pos);
	free(gm->player);
}

void	free_file_and_maps(t_game *gm)
{
	if (gm->file->map_lst)
		ft_lstclear(&gm->file->map_lst, clean_lst);
	if (gm->file->path_no)
		free(gm->file->path_no);
	if (gm->file->path_so)
		free(gm->file->path_so);
	if (gm->file->path_we)
		free(gm->file->path_we);
	if (gm->file->path_ea)
		free(gm->file->path_ea);
	if (gm->file->color_f)
		free(gm->file->color_f);
	if (gm->file->color_c)
		free(gm->file->color_c);
	free(gm->file);
	if (gm->map)
		ft_cleanup_strs(gm->map);
	if (gm->map_checker)
		ft_cleanup_strs(gm->map_checker);
}

void	end_game(t_game *gm)
{
	if (!gm || !gm->file)
		return ;
	free_file_and_maps(gm);
	if (gm->raycast.map)
		free(gm->raycast.map);
	if (gm->raycast.side_dist)
		free(gm->raycast.side_dist);
	if (gm->raycast.delta_dist)
		free(gm->raycast.delta_dist);
	if (gm->raycast.dir)
		free(gm->raycast.dir);
	destroy_scene_and_player(gm);
	if (gm->image_buffer.img)
		mlx_destroy_image(gm->mlx, gm->image_buffer.img);
	if (gm->win)
		mlx_destroy_window(gm->mlx, gm->win);
	if (gm->mlx)
	{
		mlx_do_key_autorepeaton(gm->mlx);
		mlx_destroy_display(gm->mlx);
		free(gm->mlx);
	}
}
