/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:09:58 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/08 16:22:08 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	looking_left(t_ray *ray, float x, float y);
void	looking_right(t_ray *ray, float x, float y);
void	looking_up_down(t_ray *ray, float x, float y);

static void	looking_downh(t_ray *ray, float x, float y)
{
	float	a_tan;

	a_tan = -1 / tan(ray->angle);
	ray->y_coord = floor(y) + 1;
	ray->x_coord = ((y - ray->y_coord) * a_tan + x);
	ray->step_y = TILESIZE;
	ray->step_x = (-ray->step_y) * a_tan;
}

static void	looking_uph(t_ray *ray, float x, float y)
{
	float	a_tan;

	a_tan = -1 / tan(ray->angle);
	ray->y_coord = floor(y) - 0.0001;
	ray->x_coord = (y - ray->y_coord) * a_tan + x;
	ray->step_y = -TILESIZE;
	ray->step_x = (-ray->step_y) * a_tan;
}

static void	looking_left_righth(t_ray *ray, float x, float y)
{
	ray->x_coord = x;
	ray->y_coord = y;
	ray->step_x = 0;
	ray->step_y = 1;
}

void	looking_left(t_ray *ray, float x, float y)
{
	float	a_tan;

	a_tan = -tan(ray->angle);
	ray->x_coord = floor(x) - 0.0001;
	ray->y_coord = (x - ray->x_coord) * a_tan + y;
	ray->step_x = -TILESIZE;
	ray->step_y = (-ray->step_x) * a_tan;
}

void	looking_right(t_ray *ray, float x, float y)
{
	float	a_tan;

	a_tan = -tan(ray->angle);
	ray->x_coord = floor(x) + 1;
	ray->y_coord = ((x - ray->x_coord) * a_tan + y);
	ray->step_x = TILESIZE;
	ray->step_y = -TILESIZE * a_tan;
}

void	looking_up_down(t_ray *ray, float x, float y)
{
	ray->x_coord = x;
	ray->y_coord = y;
	ray->step_x = 1;
	ray->step_y = 0;
	printf("updown\n");
}

static void	init_horizontal(float x, float y, t_ray *ray)
{
	// float	a_tan;
	if (fabs(ray->angle) > 0.0f && fabs(ray->angle) < PI)
		looking_downh(ray, x, y);
	else if (fabs(ray->angle) > PI && fabs(ray->angle) < (PII))
		looking_uph(ray, x, y);
	else if (fabs(ray->angle) == 0 || fabs(ray->angle) == PI)
		looking_left_righth(ray, x, y);
}

static void	init_vertical(float x, float y, t_ray *ray)
{
	// float	a_tan;
	if ((double)fabs(ray->angle) > PI2 && (double)fabs(ray->angle) < (PI3))
		looking_left(ray, x, y);
	else if ((double)fabs(ray->angle) > (double)(PI3) || (double)fabs(ray->angle) < PI2)
		looking_right(ray, x, y);
	else if ((double)fabs(ray->angle) == PI2 || (double)fabs(ray->angle) == (PI3))
		looking_up_down(ray, x, y);
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
		//printf("loop\n");
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
	printf("vertical %f\n", angle);
	vertical_dist = vertical_ray(x, y, &cub()->ray);
	init_ray(cub(), angle);
	printf("horizontal %f\n", angle);
	horizontal_dist = horizontal_ray(x, y, &cub()->ray);
	printf("pass horizontal\n");
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
