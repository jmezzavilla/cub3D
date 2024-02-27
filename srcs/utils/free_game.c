/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:24:12 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/27 13:46:45 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_lst(void *item)
{
	if (item)
		free(item);
}

void	free_door(t_game *game)
{
	int		i;
	t_door	*door;
	t_list	*cur;

	i = 0;
	cur = game->doors;
	while (i < TOTAL_SPRITE_EXIT)
	{
		if (game->scene->exit[i].img)
			mlx_destroy_image(game->mlx, game->scene->exit[i].img);
		i++;
	}
	while (cur)
	{
		door = cur->content;
		free(door->pos);
		cur = cur->next;
	}
	ft_lstclear(&game->doors, clean_lst);
}

void	free_scene_and_player(t_game *game)
{
	if (game->scene)
	{
		if (game->scene->text_no.img)
			mlx_destroy_image(game->mlx, game->scene->text_no.img);
		if (game->scene->text_so.img)
			mlx_destroy_image(game->mlx, game->scene->text_so.img);
		if (game->scene->text_we.img)
			mlx_destroy_image(game->mlx, game->scene->text_we.img);
		if (game->scene->text_ea.img)
			mlx_destroy_image(game->mlx, game->scene->text_ea.img);
		free_door(game);
		free(game->scene);
	}
	if (!game->player)
		return ;
	free(game->player->dir);
	free(game->player->plane);
	free(game->player->pos);
	free(game->player);
}

void	free_file_and_maps(t_game *game)
{
	if (game->file->path_no)
		free(game->file->path_no);
	if (game->file->path_so)
		free(game->file->path_so);
	if (game->file->path_we)
		free(game->file->path_we);
	if (game->file->path_ea)
		free(game->file->path_ea);
	if (game->file->color_f)
		free(game->file->color_f);
	if (game->file->color_c)
		free(game->file->color_c);
	if (game->file->map_lst)
		ft_lstclear(&game->file->map_lst, clean_lst);
	free(game->file);
	if (game->map)
		ft_cleanup_strs(game->map);
	if (game->map_checker)
		ft_cleanup_strs(game->map_checker);
}

void	free_game(t_game *game)
{
	if (!game || !game->file)
		return ;
	free_file_and_maps(game);
	if (game->raycast.map)
		free(game->raycast.map);
	if (game->raycast.side_dist)
		free(game->raycast.side_dist);
	if (game->raycast.delta_dist)
		free(game->raycast.delta_dist);
	if (game->raycast.dir)
		free(game->raycast.dir);
	free_scene_and_player(game);
	if (game->image_buffer.img)
		mlx_destroy_image(game->mlx, game->image_buffer.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_do_key_autorepeaton(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
