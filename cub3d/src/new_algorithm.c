/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:09:58 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/03/07 22:04:56 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void init_ray(t_cub3d *cub3d, float angle)
{
	cub3d->ray = protected_calloc(1, sizeof(t_ray));
	cub3d->ray->angle = angle;
	cub3d->ray->hit = 0;
	cub3d->ray->right = is_right(angle);
	cub3d->ray->up = is_up(angle);
}

static float	horizontal_ray(float x, float y, t_ray *ray)
{
	float		a_tan;

	a_tan = -1 / tan(ray->angle);
	if (ray->up == -1)
		ray->y_coord = floor(y) + 1;
	else if (ray->up == 1)
		ray->y_coord = floor(y) - 0.0001;
	ray->x_coord = ((y - ray->y_coord) * a_tan + x);
	ray->step_y = (ray->up);
	ray->step_x = (-ray->step_y) * a_tan;
	if (ray->angle == 0 || ray->angle == 3.1415926535)
	{
		ray->x_coord = x;
		ray->y_coord = y;
		ray->hit = 1;
	}
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
	print_square(cub(), (int)ray->x_coord * 32, (int)ray->y_coord * 32, create_trgb(1, 255, 0, 255));
	return(pow(ray->x_coord - x, 2) + pow(ray->y_coord - y, 2));
}

static float	vertical_ray(float x, float y, t_ray *ray)
{
	float	a_tan;
	
	a_tan = -tan(ray->angle);
	if (ray->right == -1)
		ray->x_coord = floor(x) - 0.0001;
	else if (ray->right == 1)
		ray->x_coord = floor(x) + 1;
	ray->y_coord = (x - ray->x_coord) * a_tan + y;
	ray->step_x = ray->right;
	ray->step_y = (-ray->step_x) * a_tan;
	while (!ray->hit)
	{
		if (ray->x_coord > 0 && ray->y_coord > 0 && ray->x_coord < cub()->map_x + 1 && ray->y_coord < cub()->map_y)
		{
			if (cub()->map[(int)ray->y_coord][(int)ray->x_coord] == '1')
				ray->hit = 1;
			else
			{
				ray->x_coord += ray->step_x;
				ray->y_coord += ray->step_y;
			}
		}
		else
			ray->hit = 1;
	}
	return(pow(ray->x_coord - x, 2) + pow(ray->y_coord - y, 2));





	// float new_x;
	// float new_y;
	// (void)y;
	// float angle = ray->angle;
	// if (is_right(angle) == 1)
	// {
	// 	new_x = floor(x) + 1;
	// 	new_y = y - (x - new_x) * (-tan(angle));
	// 	print_square(cub(), floor(new_x)* 32, floor(new_y) * 32, create_trgb(1, 255, 125, 125));
	// 	while (new_x < 28 && new_y >= 0 && new_y < cub()->map_y && cub()->map[(int)new_y][(int)new_x] != '1')
	// 	{
	// 		new_x += 1;
	// 		new_y += (-tan(angle)) * 1;
	// 		printf("%f, %f\n", ceil(tan(angle) * 1), new_y);
	// 		print_square(cub(), (int)new_x * 32, (int)new_y * 32, create_trgb(1, 255, 125, 255));
	// 	}
	// 	print_square(cub(), (int)new_x * 32, (int)new_y * 32, create_trgb(1, 255, 255, 125));
	// 	return ((new_x - x) / cos(angle) );
	// }
	// else
	// {
	// 	new_x = floor(x);
	// 	new_y = floor(tan(angle) * (new_x - x));
	// 	while (new_x > 0 && cub()->map[(int)new_y][(int)new_x] != '1')
	// 	{
	// 		new_x--;
	// 		new_y = floor(tan(angle) * (ZOOM));
	// 	}
	// 	//print_square(cub(), floor(new_x)* 32, floor(new_y + y) * 32, create_trgb(1, 255, 125, 125));
	// 	return ((x - new_x) / cos(angle));
	// }
}

void raycast(float x, float y, float angle)
{
	float vertical_dist;
	float horizontal_dist;
	float final_dist;

	if ((int)to_deg(angle) == 90 || (int)to_deg(angle) == -90 || (int)to_deg(angle) == 270 || (int)to_deg(angle) == -270)
		handle_ninety(x, y, angle);
	else
	{
		init_ray(cub(), angle);
		vertical_dist = vertical_ray(x, y, cub()->ray);
		free(cub()->ray);
		init_ray(cub(), angle);
		horizontal_dist = horizontal_ray(x, y, cub()->ray);
		free(cub()->ray);
		final_dist = vertical_dist < horizontal_dist ? sqrt(vertical_dist) : sqrt(horizontal_dist);
		// (void)vertical_dist;
		// final_dist = sqrt(horizontal_dist);
		printf("%f, %f\n", sqrt(vertical_dist), sqrt(horizontal_dist));
		for (int i = 0; i <= final_dist * ZOOM; i++)
		{
			int new_x = round(cub()->player.x * ZOOM + i * cos(angle));
			int new_y = round(cub()->player.y * ZOOM + i * sin(angle));
			my_mlx_pixel_put(cub()->img_2d, new_x, new_y, create_trgb(1, 255, 0, 0));
		}
	}
}