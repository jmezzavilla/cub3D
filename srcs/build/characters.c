/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:30:46 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 18:43:06 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_dir(t_player **player, int x, int y, char c)
{
	*player = ft_calloc(sizeof(t_player), 1);
	if (!*player)
		error_msg("Memory allocation - player"); // 2/3
	(*player)->pos = set_coord((double)y + 0.5, (double)x + 0.5);
	if (c == 'N')
	{
		(*player)->dir = set_coord((double)-1, (double)0);
		(*player)->plane = set_coord((double)0, (double)0.66);
	}
	else if (c == 'S')
	{
		(*player)->dir = set_coord((double)1, (double)0);
		(*player)->plane = set_coord((double)0, (double)-0.66);
	}
	else if (c == 'E')
	{
		(*player)->dir = set_coord((double)0, (double)1);
		(*player)->plane = set_coord((double)0.66, (double)0);
	}
	else if (c == 'W')
	{
		(*player)->dir = set_coord((double)0, (double)-1);
		(*player)->plane = set_coord((double)-0.66, (double)0);
	}
}

void	build_player(void)
{
	int	x;
	int	y;

	y = 0;
	while (gm()->map[y])
	{
		x = 0;
		while (gm()->map[y][x])
		{
			if (gm()->map[y][x] == 'N' || gm()->map[y][x] == 'S'
				|| gm()->map[y][x] == 'E' || gm()->map[y][x] == 'W')
			{
				set_player_dir(&gm()->player, x, y, gm()->map[y][x]);
				gm()->map[y][x] = '0';
				gm()->nbr_player++;
			}
			x++;
		}
		y++;
	}
}
