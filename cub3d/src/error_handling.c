/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:43:20 by jocaetan          #+#    #+#             */
/*   Updated: 2023/01/27 21:43:21 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	program_errors(char *errname, bool clear, bool stop)
{
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
