/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:01:02 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/01 17:01:15 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

bool	check_collisions(double move_x, double move_y);

void	move(double relative_angle)
{
	double	final_angle;
	double	move_x;
	double	move_y;

	final_angle = cub()->player.angle + relative_angle;
	move_x = 0.25 * cos(final_angle);
	move_y = 0.25 * sin(final_angle);
	if (check_collisions(move_x, move_y))
		return ;
	cub()->player.x += move_x;
	cub()->player.y += move_y;
}

bool	check_collisions(double move_x, double move_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(cub()->player.x + move_x);
	map_y = (int)floor(cub()->player.y + move_y);
	if (cub()->map[map_y][map_x] == '1')
		return (true);
	return (false);
}
