/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:42 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/24 02:24:25 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *message)
{
	dprt(2, "\033[1;31mError\n%s\033[0m\n", message);
	free_game(gm());
	exit(EXIT_FAILURE);
}

int	get_nbr(char *color, char **split_rgb)
{
	int	nbr;

	if (!color)
	{
		free(color);
		ft_cleanup_strs(split_rgb);
		error_msg("Empty color");
	}
	if (!ft_isnumber(color))
	{
		free(color);
		ft_cleanup_strs(split_rgb);
		error_msg("Color must be a number");
	}
	nbr = ft_atoi(color);
	free(color);
	if (nbr < 0 || nbr > 255)
	{
		ft_cleanup_strs(split_rgb);
		error_msg("Invalid color");
	}
	return (nbr);
}
