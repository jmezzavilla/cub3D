/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:03 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/27 13:46:41 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*elem(char *result, char *cur, char **sp, char *line)
{
	int	size;

	if (cur)
	{
		close(gm()->fd);
		free(line);
		ft_cleanup_strs(sp);
		error_msg("More than one texture/color");
	}
	size = ft_strlen(result) - 1;
	if (result[size] == '\n')
		result[size] = '\0';
	return (ft_strdup(result));
}

void	read_elements(char *line)
{
	char	**sp;
	size_t	i;
	size_t	idxn;

	sp = ft_split(line, ' ');
	i = ft_strlen_matrix(sp);
	idxn = ft_strlen(sp[i - 1]);
	sp[i - 1][idxn - 1] = '\0';
	if (!ft_strcmp(sp[0], "NO"))
		(gm()->file->path_no) = elem(sp[i - 1], gm()->file->path_no, sp, line);
	else if (!ft_strcmp(sp[0], "SO"))
		(gm()->file->path_so) = elem(sp[i - 1], gm()->file->path_so, sp, line);
	else if (!ft_strcmp(sp[0], "WE"))
		(gm()->file->path_we) = elem(sp[i - 1], gm()->file->path_we, sp, line);
	else if (!ft_strcmp(sp[0], "EA"))
		(gm()->file->path_ea) = elem(sp[i - 1], gm()->file->path_ea, sp, line);
	else if (!ft_strcmp(sp[0], "F"))
		(gm()->file->color_f) = elem(line + 2, gm()->file->color_f, sp, line);
	else if (!ft_strcmp(sp[0], "C"))
		(gm()->file->color_c) = elem(line + 2, gm()->file->color_c, sp, line);
	ft_cleanup_strs(sp);
	if (i != 2 && line[0] != '\n' && line[0] != 'F' && line[0] != 'C')
		return (close(gm()->fd), free(line), error_msg("Invalid texture"));
}

void	read_get_next_line(char *line, bool *map, bool *nl)
{
	if ((is_map(line) || *map))
	{
		if (ft_strcmp(line, "\n") && (!is_map(line) || *nl))
		{
			close(gm()->fd);
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
		read_elements(line);
}

void	read_file(void)
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
		line = get_next_line(gm()->fd);
		if (!line)
			break ;
		read_get_next_line(line, &map, &nl);
		free(line);
	}
}

void	build_file(char *map_path)
{
	check_map_extension(map_path);
	(gm()->fd) = open(map_path, O_RDONLY);
	if (gm()->fd == -1)
		error_msg("File not found");
	read_file();
	close(gm()->fd);
	if (!gm()->file->map_lst)
		error_msg("Cannot read map");
	gm()->map = convert_lst_to_char(gm()->file->map_lst);
	gm()->map_checker = convert_lst_to_char(gm()->file->map_lst);
}
