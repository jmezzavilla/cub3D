/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:51 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/20 22:50:40 by jealves-         ###   ########.fr       */
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
	int	raycast;

	raycast = 0;
	if (raycast)
	{
		(void)ac;
		(void)av;
		// build(av[1]);
		cub3d_init();
		key_hook(0);
		mlx_hook(gm()->win, KeyPress, KeyPressMask, key_hook, gm());
		mlx_hook(gm()->win, 17, 0, quit_old, NULL);
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
