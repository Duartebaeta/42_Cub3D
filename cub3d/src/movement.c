/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:01:02 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/04/18 17:46:59 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void move_w(double angle)
{
	printf("%f\n", angle);
	if (cub()->player.angle == 3.1415926535 / 2)
		cub()->player.y -= 0.25;
	else if (cub()->player.angle == -2 / 3.1415926535)
		cub()->player.y += 0.25;
	else
	{
		printf("enter");
		if (is_right(angle) == 1)
		{
			if (is_up(angle) == 1)
			{
				cub()->player.y -= sin(fabs(angle)) * 0.25;
				cub()->player.x += cos(fabs(angle)) * 0.25;
			}
			else
			{
				cub()->player.y += sin(fabs(angle)) * 0.25;
				cub()->player.x += cos(fabs(angle)) * 0.25;
			}
		}
		else
		{
			cub()->player.y += 0.25;
		}
	}
}