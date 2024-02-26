/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:51:22 by analexan          #+#    #+#             */
/*   Updated: 2024/02/23 18:59:59 by analexan         ###   ########.fr       */
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

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_file
{
	t_list		*map_lst;
	t_list		*gnl;
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

typedef struct s_raycast
{
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	t_coord		*map;
	t_coord		*side_dist;
	t_coord		*delta_dist;
	t_coord		*dir;
}				t_raycast;

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

typedef struct s_scene
{
	t_buffer	text_no;
	t_buffer	text_so;
	t_buffer	text_we;
	t_buffer	text_ea;
	int			color_f;
	int			color_c;
	t_buffer	exit[TOTAL_SPRITE_EXIT];
}				t_scene;

typedef struct s_controls
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	bool		minimap_view;
}				t_controls;

typedef struct s_door
{
	t_coord		*pos;
	bool		open;
	int			img_pos;
	int			animation;
}				t_door;

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
	int			mouse_on;
	t_scene		*scene;
	t_raycast	raycast;
	t_controls	controls;
	t_list		*doors;
}				t_game;

// cub3d
t_game			*gm(void);

/// action
// colision
void			check_colision(char **map, double x, double y, t_coord *pos);

// direction
void			move_right(char **map, t_player *player);
void			move_left(char **map, t_player *player);
void			move_front(char **map, t_player *player);
void			move_back(char **map, t_player *player);
// hook
int				quit(void);
void			hook(void);
// mouse
int				mouse_click(int button, int m_x, int m_y, t_game *game);
int				mouse_move(int m_x, int m_y, t_game *game);

/// build
// characters
void			build_player(void);
// file
void			build_file(char *map_path);
// game
void			build(char *map_path);
// scene
void			build_scene(void);

/// checker
// check_map
void			check_map(void);
// check
void			check_map_extension(char *map_path);
void			check(void);
// floodfill
void			floodfill(char **map);

/// draw
// draw_minimap
void			draw_minimap(t_game *game);
// draw_pixels
void			put_pixel(t_buffer *img, int x, int y, int color);
int				get_pixel_color(t_buffer *sprite, int x, int y);
void			draw(int x, int y, t_buffer *sprite, t_game *game);
// draw_player
void			rotate_left(t_player *player);
void			rotate_right(t_player *player);
void			event_player(t_game *game);
// raycast_tex
void			draw_wall(int x, int draw_start, int draw_end, t_door *door);
void			paint_floor(int color, int x, int d_end, t_game *game);
void			paint_ceiling(int color, int x, int d_start, t_game *game);
// raycast
void			raycast(t_game *game);

/// utils
// clean
bool			is_map(char *line);
void			clear_screen(void);
void			ft_cleanup_strs(char **strs);
// free_game
void			free_game(t_game *gm);
// msg
void			error_msg(char *message);
// utils
char			**convert_lst_to_char(t_list *lst);
bool			is_map_char(char c);
t_coord			*set_coord(double y, double x);
int				argb(double a, int r, int g, int b);

t_door			*get_door(int y, int x);
void			build_door(void);
void			open_door(t_player *player);
t_buffer		*action_door(t_door *door);

#endif
