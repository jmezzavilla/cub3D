/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:12:06 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/23 18:38:06 by analexan         ###   ########.fr       */
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

	if (!sprite_path)
		error_msg("No sprite path");
	fd_xpm = open(sprite_path, O_RDONLY);
	if (fd_xpm == -1)
		error_msg("Cannot open sprite");
	close(fd_xpm);
	load_sprite(sprite_path, target);
	fd_xpm = -1;
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
	{
		ft_cleanup_strs(split_rgb);
		error_msg("Invalid color pattern");
	}
	red = get_nbr(ft_strtrim(split_rgb[0], " "), split_rgb);
	green = get_nbr(ft_strtrim(split_rgb[1], " "), split_rgb);
	blue = get_nbr(ft_strtrim(split_rgb[2], " "), split_rgb);
	*color = argb(0.1, red, green, blue);
	ft_cleanup_strs(split_rgb);
}

void	build_scene(void)
{
	(gm()->scene) = ft_calloc(sizeof(t_scene), 1);
	if (!gm()->scene)
		error_msg("Memory allocation - scene");
	create_color(gm()->file->color_c, &gm()->scene->color_c);
	create_color(gm()->file->color_f, &gm()->scene->color_f);
	create_sprites(gm()->file->path_no, &gm()->scene->text_no);
	create_sprites(gm()->file->path_so, &gm()->scene->text_so);
	create_sprites(gm()->file->path_we, &gm()->scene->text_we);
	create_sprites(gm()->file->path_ea, &gm()->scene->text_ea);
	create_sprites("./sprites/exit0.xpm", &gm()->scene->exit[0]);
	create_sprites("./sprites/exit1.xpm", &gm()->scene->exit[1]);
	create_sprites("./sprites/exit2.xpm", &gm()->scene->exit[2]);
	create_sprites("./sprites/exit3.xpm", &gm()->scene->exit[3]);
	create_sprites("./sprites/exit4.xpm", &gm()->scene->exit[4]);
	create_sprites("./sprites/exit5.xpm", &gm()->scene->exit[5]);
	create_sprites("./sprites/exit6.xpm", &gm()->scene->exit[6]);
	create_sprites("./sprites/exit7.xpm", &gm()->scene->exit[7]);
	create_sprites("./sprites/exit8.xpm", &gm()->scene->exit[8]);
	create_sprites("./sprites/exit9.xpm", &gm()->scene->exit[9]);
	create_sprites("./sprites/exit10.xpm", &gm()->scene->exit[10]);
	create_sprites("./sprites/exit11.xpm", &gm()->scene->exit[11]);
}
