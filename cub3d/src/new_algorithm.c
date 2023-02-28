/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:09:58 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/02/28 18:21:36 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

float raycast(float x, float y, float angle)
{
	int	mapX;
	int	mapY;

	mapX = rd(x);
	mapY = rd(y);
	while (cub()->map[mapY][mapX] && cub()->map[mapY][mapX] != '1')
	{
		break ;
	}
	return angle;
}