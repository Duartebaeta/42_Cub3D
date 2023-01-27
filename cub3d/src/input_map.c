/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:53:55 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/01/27 02:01:21 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	get_input(t_cub3d *cub3d)
{
	char	*input;
	char	*tmp;
	char	*gnl_tmp;

	input = ft_strdup("");
	gnl_tmp = get_next_line(cub3d->fd);
	while (gnl_tmp != NULL)
	{
		if (ft_strlen(gnl_tmp) != 0)
		{
			tmp = ft_strjoin(input, gnl_tmp);
			free(input);
			input = ft_strdup(tmp);
			free(tmp);
		}
		free(gnl_tmp);
		gnl_tmp = get_next_line(cub3d->fd);
	}
	free(gnl_tmp);
	cub3d->input = ft_split(input, '\n');
	free(input);
}