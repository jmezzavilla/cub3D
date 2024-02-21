/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:27:48 by analexan          #+#    #+#             */
/*   Updated: 2024/02/21 16:00:12 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_click(int button, int m_x, int m_y, t_game *game)
{
	if (button)
		game->mouse_on = !game->mouse_on;
	(void)m_x;
	(void)m_y;
	return (0);
}

int	mouse_move(int m_x, int m_y, t_game *game)
{
	(void)m_y;
	if (!game->mouse_on)
		return (0);
	if (m_x > WIN_WIDTH / 2)
		rotate_right(game->player);
	else if (m_x < WIN_WIDTH / 2)
		rotate_left(game->player);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}
