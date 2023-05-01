/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:55:19 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/01 17:27:59 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	print_minimap(float angle)
{
	int	i;
	int	new_x;
	int	new_y;

	i = -1;
	while (++i <= cub()->ray.dist * ZOOM)
	{
		new_x = round(cub()->player.x * ZOOM + i * cos(angle));
		new_y = round(cub()->player.y * ZOOM + i * sin(angle));
		my_mlx_pixel_put(cub()->img_3d, new_x, new_y, cub()->ray.color);
	}
}

void	init_ray(t_cub3d *cub3d, float angle)
{
	cub3d->ray.angle = angle;
	cub3d->ray.hit = false;
	cub3d->ray.right = false;
	cub3d->ray.up = false;
	if (is_right(angle) == 1)
		cub3d->ray.right = true;
	if (is_up(angle) == 1)
		cub3d->ray.up = true;
	cub3d->ray.vert = 0;
}

int	is_right(float angle)
{
	if (((int)to_deg(angle) > -90 && (int)to_deg(angle) < 90)
		|| (int)to_deg(angle) < -270 || (int)to_deg(angle) > 270)
		return (1);
	return (-1);
}

int	is_up(float angle)
{
	if (((int)to_deg(angle) > 0 && (int)to_deg(angle) < 180)
		|| (int)to_deg(angle) < -180)
		return (-1);
	return (1);
}
