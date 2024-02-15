/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:12:06 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/02 21:53:37 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*path_sprite(char *sprite_path, char *sprite_name)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin("./sprites/", sprite_path);
	str2 = ft_strjoin(str1, "/");
	free(str1);
	str1 = ft_strjoin(str2, sprite_name);
	free(str2);
	str2 = ft_strjoin(str1, ".xpm");
	free(str1);
	return (str2);
}

static void	load_sprite(char *path, t_buffer *target)
{
	target->img = mlx_xpm_file_to_image(gm()->mlx, path, &target->width,
			&target->height);
	if (!target->img)
		error_msg("Corrupted Sprite");
	target->addr = mlx_get_data_addr(target->img, &target->bits_per_pixel,
			&target->line_length, &target->endian);
}

static void	create_sprites(char *sprite_path, char *sprite_name,
		t_buffer *target)
{
	char	*path;
	int		fd_xpm;

	path = path_sprite(sprite_path, sprite_name);
	fd_xpm = open(path, O_RDONLY);
	if (fd_xpm == -1)
		error_msg(ft_strjoin("Cannot open file: ", path));
	close(fd_xpm);
	load_sprite(path, target);
	free(path);
	fd_xpm = -1;
}

void	build_sprites(void)
{
	gm()->sprites = ft_calloc(sizeof(t_sprites), 1);
	create_sprites(MINIMAP, "wall", &gm()->sprites->minimap_wall);
	create_sprites(MINIMAP, "floor", &gm()->sprites->minimap_floor);
}
