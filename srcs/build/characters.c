/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:30:46 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/02 21:59:24 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	build_player(t_player **player, int x, int y, char c)
{
	*player = ft_calloc(sizeof(t_player), 1);
	if (!*player)
		error_msg("Memory allocation - player");
	(*player)->pos = build_coord((double)y, (double)x);
	if (c == 'N')
	{
		(*player)->dir = build_coord((double)-1, (double)0);
		(*player)->plane = build_coord((double)0, (double)0.66);
	}
	else if (c == 'S')
	{
		(*player)->dir = build_coord((double)1, (double)0);
		(*player)->plane = build_coord((double)0, (double)-0.66);
	}
	else if (c == 'E')
	{
		(*player)->dir = build_coord((double)0, (double)1);
		(*player)->plane = build_coord((double)0.66, (double)0);
	}
	else if (c == 'W')
	{
		(*player)->dir = build_coord((double)0, (double)-1);
		(*player)->plane = build_coord((double)-0.66, (double)0);
	}
}

void	build_characters(void)
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
				build_player(&gm()->player, x, y, gm()->map[y][x]);
				gm()->nbr_player++;	
			}
			x++;
		}
		y++;
	}
}
