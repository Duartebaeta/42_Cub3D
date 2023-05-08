/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:16:39 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/08 20:59:00 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	load_textures()
{
	cub()->no.img = mlx_xpm_file_to_image(cub()->mlx, cub()->no.addr, &cub()->no.w, &cub()->no.h);
	cub()->so.img = mlx_xpm_file_to_image(cub()->mlx, cub()->so.addr, &cub()->so.w, &cub()->so.h);
	cub()->we.img = mlx_xpm_file_to_image(cub()->mlx, cub()->we.addr, &cub()->we.w, &cub()->we.h);
	cub()->ea.img = mlx_xpm_file_to_image(cub()->mlx, cub()->ea.addr, &cub()->ea.w, &cub()->ea.h);
}