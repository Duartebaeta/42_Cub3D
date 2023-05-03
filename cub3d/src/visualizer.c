/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:17:59 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/03 20:11:44 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

float	norm_angle(float angle);
void	draw_wall(double angle, int i);
void	draw_ceiling_floor(double low_y, double hi_y, int i);

void	visualizer(t_cub3d *cub3d)
{
	double	curr_angle;
	double	angle_step;
	int		i;

	cub()->player.map_x = cub()->player.x * TILESIZE;
	cub()->player.map_y = cub()->player.y * TILESIZE;
	curr_angle = cub3d->player.angle - to_radian(FOV / 2);
	angle_step = to_radian(FOV) / W_3D;
	i = -1;
	while (++i < W_3D)
	{
		draw_wall(curr_angle, i);
		curr_angle += angle_step;
	}
}

float	norm_angle(float angle)
{
	if (angle >= (2 * M_PI))
		angle -= (2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	draw_wall(double angle, int i)
{
	double	psh;
	double	low_y;
	double	hi_y;
	double	corr_dist;

	raycast(cub()->player.x, cub()->player.y, angle, cub());
	corr_dist = cub()->ray.dist * cos(norm_angle(angle
				- cub()->player.angle)) * 2;
	psh = (H_3D / corr_dist);
	low_y = (H_3D / 2) - (psh / 2);
	hi_y = (H_3D / 2) + (psh / 2);
	draw_ceiling_floor(low_y, hi_y, i);
}

void	draw_ceiling_floor(double low_y, double hi_y, int i)
{
	double	counter;
	int		ceiling;
	int		color;

	ceiling = create_trgb(1, cub()->ceiling[0], cub()->ceiling[1],
			cub()->ceiling[2]);
	color = create_trgb(1, cub()->floor[0], cub()->floor[1], cub()->floor[2]);
	counter = -1.0;
	while (++counter <= ceil(low_y))
		my_mlx_pixel_put(cub()->img_3d, i, counter, color);
	while (counter <= hi_y)
	{
		my_mlx_pixel_put(cub()->img_3d, i, counter, cub()->ray.color);
		counter++;
	}
	while (counter <= H_3D)
	{
		my_mlx_pixel_put(cub()->img_3d, i, counter, ceiling);
		counter++;
	}
}
