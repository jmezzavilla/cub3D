/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:12:06 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 15:30:41 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_sprite(char *path, t_buffer *target)
{
	target->img = mlx_xpm_file_to_image(gm()->mlx, path, &target->width,
			&target->height);
	if (!target->img)
		error_msg("Corrupted Sprite");
	target->addr = mlx_get_data_addr(target->img, &target->bits_per_pixel,
			&target->line_length, &target->endian);
}

void	create_sprites(char *sprite_path, t_buffer *target)
{
	int	fd_xpm;

	fd_xpm = open(sprite_path, O_RDONLY);
	if (fd_xpm == -1)
		error_msg(ft_strjoin("Cannot open file: ", sprite_path));
	close(fd_xpm);
	load_sprite(sprite_path, target);
	fd_xpm = -1;
}

int	get_nbr(char *color)
{
	int	nbr;

	if (!color)
		error_msg("Empty color");
	if (!ft_isnumber(color))
		error_msg("Color must be a number");
	nbr = ft_atoi(color);
	free(color);
	if (nbr < 0 || nbr > 255)
		error_msg("Invalid color");
	return (nbr);
}

void	create_color(char *rgb, int *color)
{
	char	**split_rgb;
	int		red;
	int		green;
	int		blue;

	if (!rgb)
		error_msg("Empty RGB");
	split_rgb = ft_split(rgb, ',');
	if (!split_rgb)
		error_msg("Invalid RGB");
	if (ft_strlen_matrix(split_rgb) != 3)
		error_msg("Invalid color pattern");
	red = get_nbr(ft_strtrim(split_rgb[0], " "));
	green = get_nbr(ft_strtrim(split_rgb[1], " "));
	blue = get_nbr(ft_strtrim(split_rgb[2], " "));
	*color = argb(0.1, red, green, blue);
	ft_cleanup_strs(split_rgb);
}

void	build_scene(void)
{
	(gm()->scene) = ft_calloc(sizeof(t_scene), 1);
	create_color(gm()->file->color_c, &gm()->scene->color_c);
	create_color(gm()->file->color_f, &gm()->scene->color_f);
	create_sprites(gm()->file->path_no, &gm()->scene->text_no);
	create_sprites(gm()->file->path_so, &gm()->scene->text_so);
	create_sprites(gm()->file->path_we, &gm()->scene->text_we);
	create_sprites(gm()->file->path_ea, &gm()->scene->text_ea);
}
