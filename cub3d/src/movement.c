/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:01:02 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/04/26 10:54:04 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void move(double relative_angle)
{
	double final_angle = cub()->player.angle + relative_angle;
	
	double move_x = 0.25 * cos(final_angle);
	double move_y = 0.25 * sin(final_angle);

	cub()->player.x += move_x;
	cub()->player.y += move_y;
}