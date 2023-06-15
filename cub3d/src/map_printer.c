/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:49:20 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/15 20:02:13 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	print_horizontal(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while (++counter < ZOOM)
		my_mlx_pixel_put(cub3d->img_3d, x + counter, y, color);
}

void	print_vertical(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while (++counter < ZOOM)
		my_mlx_pixel_put(cub3d->img_3d, x, y + counter, color);
}

void	print_square(t_cub3d *cub3d, int x, int y, int color)
{
	int	counter;

	counter = -1;
	while (++counter < ZOOM)
		print_horizontal(cub3d, x, y + counter, color);
}

void	print_player(t_cub3d *cub3d, float x, float y, int ray)
{
	static double	pi = 3.1415926535;
	double			angle;
	double			x1;
	double			y1;
	int				r;

	angle = 0;
	while (angle < 360)
	{
		r = ray;
		while (--r)
		{
			x1 = r * cos(angle * pi / 180);
			y1 = r * sin(angle * pi / 180);
			my_mlx_pixel_put(cub3d->img_3d, x + x1, y + y1,
				create_trgb(1, 70, 120, 20));
		}
		angle += 0.1;
	}
	raycast(cub3d->player.x, cub3d->player.y,
		norm_angle(cub3d->player.angle), cub3d);
}

void	print_lines(t_cub3d *cub3d)
{
	int	c;
	int	sub;
	int	white;
	int	black;

	c = -1;
	white = create_trgb(1, 255, 255, 255);
	black = create_trgb(0, 0, 0, 0);
	while (cub3d->map[++c])
	{
		sub = -1;
		while (cub3d->map[c][++sub])
		{
			if (cub3d->map[c][sub] != '1' && cub3d->map[c][sub] != '0')
				continue ;
			if (cub3d->map[c][sub] == '1')
				print_square(cub3d, sub * ZOOM, c * ZOOM, white);
			else
				print_square(cub3d, sub * ZOOM, c * ZOOM, black);
			print_horizontal(cub3d, sub * ZOOM, c * ZOOM, white);
			print_horizontal(cub3d, sub * ZOOM, (c + 1) * ZOOM, white);
			print_vertical(cub3d, sub * ZOOM, c * ZOOM, white);
			print_vertical(cub3d, (sub + 1) * ZOOM, c * ZOOM, white);
		}
	}
}
