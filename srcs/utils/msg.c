/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:42 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/03 19:16:46 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *message)
{
	dprt(2, "Error: %s\n", message);
	// end_game(gm);
	exit(EXIT_FAILURE);
}

void	msg(const char *message)
{
	prt("%s\n", message);
}
