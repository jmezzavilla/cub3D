/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:30:46 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/26 12:27:50 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 0.66 is the value of the FOV
void	set_player_dir(t_player **player, int x, int y, char c)
{
	*player = ft_calloc(sizeof(t_player), 1);
	if (!*player)
		error_msg("Memory allocation - player");
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
				if (gm()->nbr_player > 0)
					error_msg("Invalid number of players");
				set_player_dir(&gm()->player, x, y, gm()->map[y][x]);
				gm()->map[y][x] = '0';
				gm()->nbr_player++;
			}
			x++;
		}
		y++;
	}
}
