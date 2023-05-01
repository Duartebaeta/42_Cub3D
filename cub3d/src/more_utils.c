/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:15:59 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/01 17:18:22 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	rd(float n)
{
	if (round(n) - n <= 0)
		return (round(n));
	else
		return (round(n) - 1);
}

float	to_radian(float degree)
{
	return (degree * (M_PI / 180));
}

float	to_deg(float radian)
{
	return (round(radian * 57.295779513));
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
