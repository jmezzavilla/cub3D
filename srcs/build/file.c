/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:03 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/21 18:42:35 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW\t\n ", line[i]) || (i == 0 && line[i] == '\n'))
			return (false);
		i++;
	}
	return (true);
}

char	*put_elements(char *result, char *cur)
{
	if (cur)
		error_msg("More than one texture/color"); // 1... gm()->file + map_lst
	return (ft_strdup(result));
}

void	read_elements(char *line)
{
	char	**sp;
	size_t	i;
	size_t	idxn;

	sp = ft_split(line, ' ');
	free(line);
	i = ft_strlen_matrix(sp);
	idxn = ft_strlen(sp[i - 1]);
	sp[i - 1][idxn - 1] = '\0';
	if (!ft_strcmp(sp[0], "NO"))
		(gm()->file->path_no) = put_elements(sp[i - 1], gm()->file->path_no);
	else if (!ft_strcmp(sp[0], "SO"))
		(gm()->file->path_so) = put_elements(sp[i - 1], gm()->file->path_so);
	else if (!ft_strcmp(sp[0], "WE"))
		(gm()->file->path_we) = put_elements(sp[i - 1], gm()->file->path_we);
	else if (!ft_strcmp(sp[0], "EA"))
		(gm()->file->path_ea) = put_elements(sp[i - 1], gm()->file->path_ea);
	else if (!ft_strcmp(sp[0], "F"))
		(gm()->file->color_f) = put_elements(sp[i - 1], gm()->file->color_f);
	else if (!ft_strcmp(sp[0], "C"))
		(gm()->file->color_c) = put_elements(sp[i - 1], gm()->file->color_c);
	ft_cleanup_strs(sp);
}

void	read_file(int fd)
{
	char	*line;
	bool	map;

	(gm()->file) = ft_calloc(sizeof(t_file), 1);
	if (!gm()->file)
		error_msg("Memory allocation - file"); // 0 nothing
	line = NULL;
	map = false;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map(line) || map)
		{
			ft_lstadd_back(&gm()->file->map_lst, ft_lstnew(line));
			map = true;
		}
		else
			read_elements(line);
	}
}

void	build_file(char *map_path)
{
	int	fd;

	check_map_extension(map_path);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		error_msg("File not found"); // 0 nothing
	read_file(fd);
	close(fd);
	if (!gm()->file->map_lst)
		error_msg("Cannot read map"); // 2 gm()->file + map_lst + file stuff
	gm()->map = convert_lst_to_char(gm()->file->map_lst);
	gm()->map_checker = convert_lst_to_char(gm()->file->map_lst);
}
