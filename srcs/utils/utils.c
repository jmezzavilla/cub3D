/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:47 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/27 13:20:18 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**convert_lst_to_char(t_list *lst)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!str)
		error_msg("Memory allocation - lst");
	while (lst)
	{
		str[i] = ft_strdup(lst->content);
		if (!str[i])
			exit(EXIT_FAILURE);
		i++;
		lst = lst->next;
	}
	return (str);
}

bool	is_map_char(char **map, int y, int x)
{
	int	sx;

	sx = ft_strlen(map[y]) - 1;
	if (sx < x)
		return (false);
	if (map[y][x] != ' ' && map[y][x] != '\n' && map[y][x] != '\0')
		return (true);
	return (false);
}

t_coord	*set_coord(double y, double x)
{
	t_coord	*coord;

	coord = ft_calloc(sizeof(t_coord), 1);
	if (!coord)
		error_msg("Memory allocation - coord");
	coord->x = x;
	coord->y = y;
	return (coord);
}

int	argb(double a, int r, int g, int b)
{
	a = 1 - a;
	r *= a;
	g *= a;
	b *= a;
	return (r << 16 | g << 8 | b);
}

bool	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01DNSEW\t\n ", line[i]) || (i == 0 && line[i] == '\n'))
			return (false);
		i++;
	}
	return (true);
}
