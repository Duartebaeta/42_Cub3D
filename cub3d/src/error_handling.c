/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:43:20 by jocaetan          #+#    #+#             */
/*   Updated: 2023/06/15 22:34:27 by dhomem-d         ###   ########.fr       */
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

void	check_extra_lines(void)
{
	int	last_map_line;

	last_map_line = 6 + cub()->map_y;
	last_map_line--;
	while (cub()->file[++last_map_line])
	{
		if (!is_empty_line(cub()->file[last_map_line]))
			program_errors("Extra lines", true, true);
	}
	return ;
}

bool	has_map_started(char *line)
{
	char	*trim;

	trim = ft_strtrim(line, " \t");
	if (trim[0] && trim[0] == '1')
	{
		free(trim);
		return (true);
	}
	free(trim);
	return (false);
}
