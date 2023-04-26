/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:09:58 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/04/26 06:57:21 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void init_ray(t_cub3d *cub3d, float angle)
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

static void init_horizontal(float x, float y, t_ray *ray)
{
	float	a_tan;

	a_tan = -1 / tan(ray->angle);
	if (!ray->up)
		ray->y_coord = floor(y) + 1;
	else if (ray->up)
		ray->y_coord = floor(y) - 0.0001;
	ray->x_coord = ((y - ray->y_coord) * a_tan + x);
	ray->step_y = (-is_up(ray->angle));
	ray->step_x = (-ray->step_y) * a_tan;
	if (ray->angle == 0 || ray->angle == 3.1415926535)
	{
		ray->x_coord = x;
		ray->y_coord = y;
		ray->hit = 1;
	}
}

static void	init_vertical(float x, float y, t_ray *ray)
{
	float	a_tan;

	if (ray->angle == 3.1415926535 / 2 || ray->angle == -2 / 3.1415926535)
	{
		ray->x_coord = x;
		ray->y_coord = y;
		ray->step_x = 0;
		ray->step_y = 0;
	}
	else
	{
		a_tan = -tan(ray->angle);
		if (!ray->right)
			ray->x_coord = floor(x) - 0.0001;
		else if (ray->right)
			ray->x_coord = floor(x) + 1;
		ray->y_coord = (x - ray->x_coord) * a_tan + y;
		ray->step_x = is_right(ray->angle);
		ray->step_y = (-ray->step_x) * a_tan;
	}
}

static float	horizontal_ray(float x, float y, t_ray *ray)
{
	init_horizontal(x, y, ray);
	while (!ray->hit)
	{
		if (ray->x_coord > 0 && ray->y_coord > 0 && ray->x_coord < cub()->map_x + 1 && ray->y_coord < cub()->map_y)
		{
			if (cub()->map[(int)ray->y_coord][(int)ray->x_coord] == '1')
				ray->hit = 1;
			else
			{
				ray->x_coord += (ray->step_x);
				ray->y_coord += (ray->step_y);
			}
		}
		else
			ray->hit = 1;
	}
	return(pow(ray->x_coord - x, 2) + pow(ray->y_coord - y, 2));
}

static float	vertical_ray(float x, float y, t_ray *ray)
{
	init_vertical(x, y, ray);
	while (!ray->hit)
	{
		if (ray->x_coord > 0 && ray->y_coord > 0 && ray->x_coord < cub()->map_x + 1 && ray->y_coord < cub()->map_y)
		{
			if (cub()->map[(int)ray->y_coord][(int)ray->x_coord] == '1')
				ray->hit = true;
			else
			{
				ray->x_coord += ray->step_x;
				ray->y_coord += ray->step_y;
			}
		}
		else
			ray->hit = true;
	}
	return(pow(ray->x_coord - x, 2) + pow(ray->y_coord - y, 2));
}

void raycast(float x, float y, float angle)
{
	float vertical_dist;
	float horizontal_dist;
	float final_dist;

	init_ray(cub(), angle);
	vertical_dist = vertical_ray(x, y, &cub()->ray);
	init_ray(cub(), angle);
	horizontal_dist = horizontal_ray(x, y, &cub()->ray);
	if (vertical_dist < horizontal_dist)
	{
		cub()->ray.vert = 1;
		final_dist = sqrt(vertical_dist);
	}
	else
		final_dist = sqrt(horizontal_dist);
	cub()->ray.dist = final_dist;
	cub()->ray.color = vertical_dist < horizontal_dist ? create_trgb(1, 255, 0, 0) : create_trgb(1, 0, 255, 0);
	for (int i = 0; i <= final_dist * ZOOM; i++)
	{
		int new_x = round(cub()->player.x * ZOOM + i * cos(angle));
		int new_y = round(cub()->player.y * ZOOM + i * sin(angle));
		my_mlx_pixel_put(cub()->img_3d, new_x, new_y, cub()->ray.color);
	}
}
