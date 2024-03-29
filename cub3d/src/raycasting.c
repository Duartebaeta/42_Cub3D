/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:09:58 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/15 20:03:09 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	init_horizontal(float x, float y, t_ray *ray)
{
	float	a_tan;

	if ((ray->angle) > 0.0f && (ray->angle) < PI)
	{
		a_tan = -1 / tan(ray->angle);
		ray->y_coord = floor(y) + 1;
		ray->x_coord = ((y - ray->y_coord) * a_tan + x);
		ray->step_y = TILESIZE;
		ray->step_x = (-ray->step_y) * a_tan;
	}
	else if ((ray->angle) > PI && (ray->angle) < (PII))
	{
		a_tan = -1 / tan(ray->angle);
		ray->y_coord = floor(y) - 0.0001;
		ray->x_coord = (y - ray->y_coord) * a_tan + x;
		ray->step_y = -TILESIZE;
		ray->step_x = (-ray->step_y) * a_tan;
	}
	else if ((ray->angle) == 0 || (ray->angle) == PI)
	{
		ray->x_coord = x;
		ray->y_coord = y;
		ray->step_x = 0;
		ray->step_y = 1;
	}
}

static void	init_vertical(float x, float y, t_ray *ray)
{
	float	a_tan;

	if ((double)(ray->angle) > PI2 && (double)(ray->angle) < (PI3))
	{
		a_tan = -tan(ray->angle);
		ray->x_coord = floor(x) - 0.0001;
		ray->y_coord = (x - ray->x_coord) * a_tan + y;
		ray->step_x = -TILESIZE;
		ray->step_y = (-ray->step_x) * a_tan;
	}
	else if ((double)(ray->angle) > (double)(PI3) || (double)(ray->angle) < PI2)
	{
		a_tan = -tan(ray->angle);
		ray->x_coord = floor(x) + 1;
		ray->y_coord = ((x - ray->x_coord) * a_tan + y);
		ray->step_x = TILESIZE;
		ray->step_y = -TILESIZE * a_tan;
	}
	else if ((double)(ray->angle) == PI2 || (double)(ray->angle) == (PI3))
	{
		ray->x_coord = x;
		ray->y_coord = y;
		ray->step_x = 1;
		ray->step_y = 0;
	}
}

static float	horizontal_ray(float x, float y, t_ray *ray)
{
	init_horizontal(x, y, ray);
	while (!ray->hit)
	{
		if (ray->x_coord > 0 && ray->y_coord > 0 && ray->x_coord < cub()->map_x
			+ 1 && ray->y_coord < cub()->map_y)
		{
			if (cub()->map[(int)ray->y_coord][(int)ray->x_coord] == '1')
				ray->hit = 1;
			else
			{
				ray->x_coord += (ray->step_x) / TILESIZE;
				ray->y_coord += (ray->step_y) / TILESIZE;
			}
		}
		else
			ray->hit = 1;
	}
	cub()->ray.x_dist = ray->x_coord - (float)floor(ray->x_coord);
	return (pow(ray->x_coord - x, 2) + pow(ray->y_coord - y, 2));
}

static float	vertical_ray(float x, float y, t_ray *ray)
{
	init_vertical(x, y, ray);
	while (!ray->hit)
	{
		if (ray->x_coord > 0 && ray->y_coord > 0 && ray->x_coord < cub()->map_x
			+ 1 && ray->y_coord < cub()->map_y)
		{
			if (cub()->map[(int)ray->y_coord][(int)ray->x_coord] == '1')
				ray->hit = true;
			else
			{
				ray->x_coord += ray->step_x / TILESIZE;
				ray->y_coord += ray->step_y / TILESIZE;
			}
		}
		else
			ray->hit = true;
	}
	cub()->ray.y_dist = ray->y_coord - (float)floor(ray->y_coord);
	return (pow(ray->x_coord - x, 2) + pow(ray->y_coord - y, 2));
}

void	raycast(float x, float y, float angle, t_cub3d *cub3d)
{
	float	vertical_dist;
	float	horizontal_dist;
	float	final_dist;

	init_ray(cub(), angle);
	vertical_dist = vertical_ray(x, y, &cub()->ray);
	init_ray(cub(), angle);
	horizontal_dist = horizontal_ray(x, y, &cub()->ray);
	cub3d->ray.color = create_trgb(1, 0, 255, 0);
	if (vertical_dist < horizontal_dist)
	{
		cub()->ray.vert = 1;
		cub()->ray.calc_dist = cub()->ray.y_dist;
		final_dist = sqrt(vertical_dist);
	}
	else
	{
		final_dist = sqrt(horizontal_dist);
		cub()->ray.calc_dist = cub()->ray.x_dist;
	}
	cub()->ray.dist = final_dist;
	set_cardinal(angle);
	if (cub()->minimap)
		print_minimap(angle);
}
