/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:51 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/15 16:45:44 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*gm(void)
{
	static t_game	game;

	return (&game);
}

int	cub3d(char *map_path)
{
	build(map_path);
	hook();
	return (1);
}

int	main(int ac, char **av)
{
	int raycast = 0;
	
	if (raycast)
	{
		(void)ac;
		(void)av;
		cub3d_init();
		key_hook(0);
		mlx_hook(gm()->win, KeyPress, KeyPressMask, key_hook, NULL);
		mlx_hook(gm()->win, 17, 0, quit, &gm);
		mlx_loop(gm()->mlx);
	}
	else
	{
		if (ac == 2)
			return (cub3d(av[1]));
		else
			error_msg("Invalid Number of Arguments");
	}
	return (0);
}
