/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                            :+:      :+:    :+:   */
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
	t_sprite	*sprite;
	t_list	*cur;

	i = 0;
	cur = game->sprites;
	while (i < TOTAL_SPRITE_ENEMY)
	{
		if (game->scene->enemy[i].img)
			mlx_destroy_image(game->mlx, game->scene->enemy[i].img);
		i++;
	}
	while (cur)
	{
		sprite = cur->content;
		if(sprite->type == 'M')
			free(sprite->pos);
		cur = cur->next;
	}
	ft_lstclear(&game->sprites, clean_lst);
}

t_buffer	*action_enemy(t_sprite *sprite)
{
	if (sprite->animation == 1000)
	{
		if (sprite->img_pos != (TOTAL_SPRITE_ENEMY - 1))
			sprite->img_pos += 1;
		else
			sprite->img_pos = 0;
		sprite->animation = 0;
	}
	else
		sprite->animation++;
	return (&gm()->scene->enemy[sprite->img_pos]);
}

void	set_sprite(int y, int x, char type)
{
	t_sprite	*sprite;

	sprite = ft_calloc(sizeof(t_sprite), 1);
	if (!sprite)
		error_msg("Memory allocation - sprite");
	sprite->img_pos = 0;
	sprite->animation = 0;
	sprite->type = type;
	sprite->pos = set_coord((double)y + 0.5, (double)x + 0.5);
	if(type == 'B')
		printf("barril");
	if(type == 'D')
		sprite->open = false;
	ft_lstadd_back(&gm()->sprites, ft_lstnew(sprite));
}

t_sprite	*get_sprite(double y, double x)
{
	t_list	*cur;
	t_sprite	*sprite;

	cur = gm()->sprites;
	while (cur)
	{
		sprite = cur->content;
		if (sprite->pos->x == x && sprite->pos->y == y)
			return (sprite);
		cur = cur->next;
	}
	return (NULL);
}

void	build_sprites(void)
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
				set_sprite(y, x, 'M');
				gm()->map[y][x] = '0';
			}
			else if (gm()->map[y][x] == 'D')
				set_sprite(y, x, 'D');
			else if(!ft_strchr("01MDNSEW\t\n ", gm()->map[y][x]))
				set_sprite(y, x, gm()->map[y][x]);
			x++;
		}
		y++;
	}
}
