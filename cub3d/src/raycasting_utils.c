/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:55:19 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/03/14 18:33:55 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	rd(float n)
{
	return (round(n) - n <= 0 ? round(n) : round(n) - 1);
}

float	to_radian(float degree)
{
	return (degree * (3.14159 / 180));
}

float	to_deg(float radian)
{
	return (round(radian * 57.295779513));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	is_right(float angle)
{
	if (((int)to_deg(angle) > -90 && (int)to_deg(angle) < 90) || (int)to_deg(angle) < -270 || (int)to_deg(angle) > 270)
		return (1);
	return (-1);
}

int	is_up(float angle)
{
	if (((int)to_deg(angle) > 0 && (int)to_deg(angle) < 180) || (int)to_deg(angle) < -180)
		return (-1);
	return (1);
}