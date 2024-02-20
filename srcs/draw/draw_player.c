#include "cub3d.h"

void	event_player(t_game *game)
{
	if (game->controls.up == W_KEY)
		move_front(game, game->player);
	if (game->controls.down == S_KEY)
		move_back(game, game->player);
	if (game->controls.left == A_KEY)
		move_left(game, game->player);
	if (game->controls.right == D_KEY)
		move_right(game, game->player);
	if(game->controls.rotate_right == RIGHT_KEY)
	{
		double	olddir_x;
		double	oldplane_x;

		olddir_x = game->player->dir->x;
		oldplane_x = game->player->plane->x;
		game->player->dir->x = game->player->dir->x * cos(game->move_speed) - game->player->dir->y * sin(game->move_speed);
		game->player->dir->y = olddir_x * sin(game->move_speed) + game->player->dir->y * cos(game->move_speed);
		game->player->plane->x = game->player->plane->x * cos(game->move_speed) \
			- game->player->plane->y * sin(game->move_speed);
		game->player->plane->y = oldplane_x * sin(game->move_speed) \
			+ game->player->plane->y * cos(game->move_speed);
	}
	if(game->controls.rotate_left == LEFT_KEY)	
	{
		double	olddir_x;
		double	oldplane_x;

		olddir_x = game->player->dir->x;
		oldplane_x = game->player->plane->x;
		game->player->dir->x = game->player->dir->x * cos(-game->move_speed) - game->player->dir->y * sin(-game->move_speed);
		game->player->dir->y = olddir_x * sin(-game->move_speed) + game->player->dir->y * cos(-game->move_speed);
		game->player->plane->x = game->player->plane->x * cos(-game->move_speed) \
			- game->player->plane->y * sin(-game->move_speed);
		game->player->plane->y = oldplane_x * sin(-game->move_speed) \
			+ game->player->plane->y * cos(-game->move_speed);
	}
}
