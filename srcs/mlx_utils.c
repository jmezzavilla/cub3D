/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:46:19 by analexan          #+#    #+#             */
/*   Updated: 2024/02/15 16:17:10 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_buffer *image, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < image->width && y < image->height)
	{
		dst = image->addr 
			+ (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
		prt("Illegal value x: %i, y: %i\n", x, y);
}

int	argb(double a, int r, int g, int b)
{
	a = 1 - a;
	r *= a;
	g *= a;
	b *= a;
	return (r << 16 | g << 8 | b);
}

	// step recebe o valor absoluto da diferenca maior
void	put_line(t_buffer *image, int x1, int y1, int x2, int y2, int color)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;
	int		i;

	dx = (float)(x2 - x1);
	dy = (float)(y2 - y1);
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		my_mlx_pixel_put(image, (int)x, (int)y, color);
		x += dx;
		y += dy;
		i++;
	}
}

void	put_square(t_buffer *image, int x1, int y1, int x2, int y2, 
		int just_perimeter, int color)
{
	int	i;

	if (just_perimeter)
	{
		put_line(image, x1, y1, x1, y2, color);
		put_line(image, x1, y1, x2, y1, color);
		put_line(image, x2, y1, x2, y2, color);
		put_line(image, x1, y2, x2, y2, color);
	}
	else
	{
		i = 0;
		while (y1 + i <= y2)
		{
			put_line(image, x1, y1 + i, x2, y1 + i, color);
			i++;
		}
	}
}

void	create_image(int width, int height, int color, t_buffer *image)
{
	int is_perimeter;
	image->width = width;
	image->height = height;
	image->img = mlx_new_image(gm()->mlx, image->width, image->height);
	image->addr = mlx_get_data_addr(image->img, 
			&image->bits_per_pixel, &image->line_length, 
			&image->endian);
	is_perimeter = (color == argb(0, 64, 64, 64));
	put_square(image, 0, 0, image->width - 1, image->height - 1, is_perimeter, color);
}
