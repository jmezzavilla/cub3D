/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:26 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/23 19:36:45 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_extension(char *map_path)
{
	char	*extension;

	extension = ft_strchr(map_path, '.');
	if (extension == NULL)
		error_msg("Map extension invalid");
	if (ft_strcmp(extension, ".cub") != 0)
		error_msg("Map extension invalid");
}

void	check_file(t_file *file)
{
	if (!file)
		error_msg("Cannot read file");
	if (!file->path_no || !ft_strlen(file->path_no))
		error_msg("Without NO texture");
	if (!file->path_so || !ft_strlen(file->path_so))
		error_msg("Without SO texture");
	if (!file->path_we || !ft_strlen(file->path_we))
		error_msg("Without WE texture");
	if (!file->path_ea || !ft_strlen(file->path_ea))
		error_msg("Without EA texture");
	if (!file->color_c || !ft_strlen(file->color_c))
		error_msg("Without ceiling color");
	if (!file->color_f || !ft_strlen(file->color_f))
		error_msg("Without floor color");
	if (ft_strcmp(file->path_no, file->path_so) == 0 || ft_strcmp(file->path_no,
			file->path_we) == 0 || ft_strcmp(file->path_no, file->path_ea) == 0
		|| ft_strcmp(file->path_so, file->path_we) == 0
		|| ft_strcmp(file->path_so, file->path_ea) == 0
		|| ft_strcmp(file->path_we, file->path_ea) == 0)
		error_msg("Repeated texture");
}

void	check(void)
{
	check_file(gm()->file);
	check_map();
	if (gm()->nbr_player != 1)
		error_msg("Invalid number of players");
}
