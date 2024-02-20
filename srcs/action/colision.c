#include "cub3d.h"


int	is_right_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y + (player->dir->y * game->move_speed);
	x = player->pos->x - (player->dir->x * game->move_speed);
	return (game->map[y][x] == '1');
}

int	is_left_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y - (player->dir->y * game->move_speed);
	x = player->pos->x + (player->dir->x * game->move_speed);
	return (game->map[y][x] == '1');
}

int	is_front_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y + (player->dir->y * game->move_speed);
	x = player->pos->x + (player->dir->x * game->move_speed);
	return (game->map[y][x] == '1');
}

int	is_back_wall(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = player->pos->y - (player->dir->y * game->move_speed);
	x = player->pos->x - (player->dir->x * game->move_speed);
	return (game->map[y][x] == '1');
}