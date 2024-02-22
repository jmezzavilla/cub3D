/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:42 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 18:53:28 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *message)
// void	error_msg(char *message, int mode)
{
	dprt(2, "Error\n%s\n", message);
	end_game(4);
	exit(EXIT_FAILURE);
}
