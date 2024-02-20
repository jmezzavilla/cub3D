/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:37 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 23:23:49 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_screen(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (gm()->map[y])
	{
		x = 0;
		while (gm()->map[y][x])
		{
			put_pixel(&gm()->image_buffer, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	ft_cleanup_strs(char **strs)
{
	size_t	idx;

	idx = 0;
	while (strs[idx])
		free(strs[idx++]);
	free(strs);
}
