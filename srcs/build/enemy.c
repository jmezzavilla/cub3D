/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:44:49 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/24 02:42:09 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_enemy(t_game *game)
{
	int		i;
	t_enemy	*enemy;
	t_list	*cur;

	i = 0;
	cur = game->enemies;
	while (i < TOTAL_SPRITE_ENEMY)
	{
		if (game->scene->enemy[i].img)
			mlx_destroy_image(game->mlx, game->scene->enemy[i].img);
		i++;
	}
	while (cur)
	{
		enemy = cur->content;
		free(enemy->pos);
		cur = cur->next;
	}
	ft_lstclear(&game->enemies, clean_lst);
}

t_buffer	*action_enemy(t_enemy *enemy)
{
	if (enemy->animation == 1000000)
	{
		if (enemy->img_pos != (TOTAL_SPRITE_ENEMY - 1))
			enemy->img_pos += 1;
		else
			enemy->img_pos = 0;
		enemy->animation = 0;
	}
	else
		enemy->animation++;
	return (&gm()->scene->enemy[enemy->img_pos]);
}

void	set_enemy(int y, int x)
{
	t_enemy	*enemy;

	enemy = ft_calloc(sizeof(t_enemy), 1);
	if (!enemy)
		error_msg("Memory allocation - enemy");
	enemy->img_pos = 0;
	enemy->animation = 0;
	enemy->pos = set_coord((double)y + 0.5, (double)x + 0.5);
	ft_lstadd_back(&gm()->enemies, ft_lstnew(enemy));
}

t_enemy	*get_enemy(double y, double x)
{
	t_list	*cur;
	t_enemy	*enemy;

	cur = gm()->enemies;
	while (cur)
	{
		enemy = cur->content;
		if (enemy->pos->x == x && enemy->pos->y == y)
			return (enemy);
		cur = cur->next;
	}
	return (NULL);
}

void	build_enemies(void)
{
	int	x;
	int	y;

	y = 0;
	while (gm()->map[y])
	{
		x = 0;
		while (gm()->map[y][x])
		{
			if (gm()->map[y][x] == 'M')
			{
				set_enemy(y, x);
				gm()->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
