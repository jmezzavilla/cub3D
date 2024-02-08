/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealves- <jealves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:32:15 by jealves-          #+#    #+#             */
/*   Updated: 2024/02/06 18:45:05 by jealves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "constants.h"
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_file
{
	t_list		*map_lst;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*color_f;
	char		*color_c;
}				t_file;

typedef struct s_player
{
	t_coord		*pos;
	t_coord		*dir;
	t_coord		*plane;
}				t_player;

typedef struct s_buffer
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_buffer;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
	int			code_rgb;
}				t_color;

typedef struct s_scene
{
	t_buffer	minimap_wall;
	t_buffer	minimap_floor;
	t_buffer	text_no;
	t_buffer	text_so;
	t_buffer	text_we;
	t_buffer	text_ea;
	t_color		color_f;
	t_color		color_c;
}				t_scene;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_file		*file;
	t_buffer	image_buffer;
	char		**map;
	char		**map_checker;
	t_player	*player;
	int			nbr_player;
	t_scene		*scene;
}				t_game;

// build_structure
t_game			*gm(void);
void			build(char *map_path);
void			build_file(char *map_path);
void			build_characters(void);
void			build_scene(void);

// msg
void			error_msg(char *message);
void			ft_cleanup_strs(char **strs);
void			msg(const char *message);

// checker
void			check(void);
void			check_map(void);
void			check_map_extension(char *map_path);
void			floodfill(char **map);

// util
char			**convert_lst_to_char(t_list *lst);
bool			is_map_char(char c);
t_coord			*build_coord(double y, double x);

// action
void			hook(void);

// draw
void			draw_minimap(t_game *game);
void			draw(int x, int y, t_buffer *sprite, t_game *game);
void			put_pixel(t_buffer *img, int x, int y, int color);

#endif
