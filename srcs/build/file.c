/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:03 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/26 14:05:25 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*elem(char *result, char *cur, int fd, char **sp, char *line)
{
	int	size;

	if (cur)
	{
		close(fd);
		free(line);
		ft_cleanup_strs(sp);
		error_msg("More than one texture/color");
	}
	size = ft_strlen(result) - 1;
	if (result[size] == '\n')
		result[size] = '\0';
	return (ft_strdup(result));
}

// NEEDS FIXIN
void	read_elements(char *line, int fd)
{
	char	**sp;
	size_t	i;
	size_t	idxn;

	sp = ft_split(line, ' ');
	i = ft_strlen_matrix(sp);
	idxn = ft_strlen(sp[i - 1]);
	sp[i - 1][idxn - 1] = '\0';
	if (!ft_strcmp(sp[0], "NO"))
		(gm()->file->path_no) = elem(sp[i - 1], gm()->file->path_no, fd, sp, line);
	else if (!ft_strcmp(sp[0], "SO"))
		(gm()->file->path_so) = elem(sp[i - 1], gm()->file->path_so, fd, sp, line);
	else if (!ft_strcmp(sp[0], "WE"))
		(gm()->file->path_we) = elem(sp[i - 1], gm()->file->path_we, fd, sp, line);
	else if (!ft_strcmp(sp[0], "EA"))
		(gm()->file->path_ea) = elem(sp[i - 1], gm()->file->path_ea, fd, sp, line);
	else if (!ft_strcmp(sp[0], "F"))
		(gm()->file->color_f) = elem(line + 2, gm()->file->color_f, fd, sp, line);
	else if (!ft_strcmp(sp[0], "C"))
		(gm()->file->color_c) = elem(line + 2, gm()->file->color_c, fd, sp, line);
	ft_cleanup_strs(sp);
	if (i != 2 && line[0] != '\n' && line[0] != 'F' && line[0] != 'C')
		return (close(fd), free(line), error_msg("Invalid texture"));
}

void	read_get_next_line(char *line, bool *map, bool *nl, int fd)
{
	if ((is_map(line) || *map))
	{
		if (ft_strcmp(line, "\n") && (!is_map(line) || *nl))
		{
			close(fd);
			free(line);
			error_msg("Invalid structure map");
		}
		if (ft_strcmp(line, "\n") == 0)
			*nl = true;
		else
			ft_lstadd_back(&gm()->file->map_lst, ft_lstnew(ft_strdup(line)));
		*map = true;
	}
	else
		read_elements(line, fd);
}

void	read_file(int fd)
{
	bool	map;
	bool	nl;
	char	*line;

	(gm()->file) = ft_calloc(sizeof(t_file), 1);
	if (!gm()->file)
		error_msg("Memory allocation - file");
	line = NULL;
	map = false;
	nl = false;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_lstadd_back(&gm()->file->gnl, ft_lstnew(line));
		read_get_next_line(line, &map, &nl, fd);
		free(line);
	}
}

void	build_file(char *map_path)
{
	int	fd;

	check_map_extension(map_path);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		error_msg("File not found");
	read_file(fd);
	close(fd);
	if (!gm()->file->map_lst)
		error_msg("Cannot read map");
	gm()->map = convert_lst_to_char(gm()->file->map_lst);
	gm()->map_checker = convert_lst_to_char(gm()->file->map_lst);
}
