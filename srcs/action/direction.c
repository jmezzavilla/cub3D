#include "cub3d.h"


void	move_right(t_game *game, t_player *player)
{
	if (!is_right_wall(game,player))
    {
        player->pos->x -= (player->dir->y * MOVE);
        player->pos->y += (player->dir->x * MOVE);
    }
}

void	move_left(t_game *game, t_player *player)
{
	if (!is_left_wall(game, player))
	{
        player->pos->x += (player->dir->y * MOVE);
        player->pos->y -= (player->dir->x * MOVE);
    }
}

void	move_front(t_game *game, t_player *player)
{
	if (!is_front_wall(game, player))
	{
        player->pos->x += (player->dir->x * MOVE);
        player->pos->y += (player->dir->y * MOVE);
    }
}

void	move_back(t_game *game, t_player *player)
{
	if (!is_back_wall(game,	player))
	{
        player->pos->x -= (player->dir->x * MOVE);
        player->pos->y -= (player->dir->y * MOVE);
    }
}