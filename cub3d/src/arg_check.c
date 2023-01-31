/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:01:54 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/01/31 16:44:22 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_input(int fd)
{
	char	*input;
	char	*tmp;
	char	*gnl_tmp;

	input = ft_strdup("");
	gnl_tmp = get_next_line(fd);
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
		gnl_tmp = get_next_line(fd);
	}
	free(gnl_tmp);
	cub()->file = ft_split(input, '\n');
	free(input);
}

int	parse_textures(t_cub3d *cub3d)
{
	int		counter;
	int		in_counter;
	char	*line;

	counter = 0;
	in_counter = -1;
	while (counter < 6 && cub3d->file[++in_counter])
	{
		line = ft_strtrim(cub3d->file[in_counter], " ");
		if (ft_strlen(line) == 0)
			free(line);
		else
		{
			if (check_textures(cub3d, line, counter))
				return (1);
			counter++;
		}
	}
	return (0);
}

int	arg_checker(char	*filename)
{
	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL)
		return (3);
	cub()->fd = open(filename, O_RDONLY);
	printf("fd: %i\n", cub()->fd);
	if (cub()->fd < 0)
	{
		if (errno == ENOENT)
		{
			printf("Error, %s does not exist.\n", filename);
			return (1);
		}
		return (2);
	}
	get_input(cub()->fd);
	if (parse_textures(cub()))
		return (1);
	return (0);
}
