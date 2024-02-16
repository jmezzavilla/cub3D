
#include "cub3d.h"

void	clean_lst(void *item)
{
	if (item)
		free(item);
}

void destroy_player(t_game *game)
{
	free(game->player->dir);
	free(game->player->plane);
	free(game->player->pos);
	free(game->player);
}

void	destroy_game(t_game *game)
{
	ft_lstclear(&game->file->map_lst, clean_lst);
	ft_cleanup_strs(game->map);
	destroy_player(game);
	mlx_destroy_image(game->mlx, game->image_buffer.img);
	mlx_destroy_image(game->mlx,game->scene->text_no.img);
	mlx_destroy_image(game->mlx,game->scene->text_ea.img);
	mlx_destroy_image(game->mlx,game->scene->text_so.img);
	mlx_destroy_image(game->mlx,game->scene->text_we.img);

	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->file->path_ea);
	free(game->file->path_so);
	free(game->file->path_we);
	free(game->file->path_no);
	free(game->file->color_c);
	free(game->file->color_f);
	free(game->mlx);
}

void	end_game()
{
	if (gm())
		destroy_game(gm());
	exit(EXIT_SUCCESS);
}
