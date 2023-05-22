/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:43:20 by jocaetan          #+#    #+#             */
/*   Updated: 2023/05/22 16:19:47 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	program_errors(char *errname, bool clear, bool stop)
{
	printf("Exiting\n");
	perror(errname);
	if (clear)
		clear_data();
	if (stop)
		exit(EXIT_FAILURE);
}

void	clear_data(void)
{
	ft_strarray_clear(&cub()->file);
	ft_strarray_clear(&cub()->map);
}
