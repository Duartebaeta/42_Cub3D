/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:01:54 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/15 22:34:12 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	input_logic(char *gnl_tmp, bool map_started, char **input)
{
	char	*tmp;

	if (is_empty_line(gnl_tmp))
	{
		if (map_started)
		{
			free(gnl_tmp);
			free(*input);
			return (1);
		}
		return (0);
	}
	else
	{
		tmp = ft_strjoin(*input, gnl_tmp);
		free(*input);
		*input = ft_strdup(tmp);
		free(tmp);
		return (0);
	}
}

static int	get_input(t_cub3d *cub3d)
{
	char	*input;
	char	*gnl_tmp;
	bool	map_started;

	gnl_tmp = get_next_line(cub3d->fd);
	if (gnl_tmp == NULL)
		return (1);
	input = ft_strdup("");
	map_started = false;
	while (gnl_tmp != NULL)
	{
		if (input_logic(gnl_tmp, map_started, &input))
			return (1);
		map_started = has_map_started(gnl_tmp);
		free(gnl_tmp);
		gnl_tmp = get_next_line(cub3d->fd);
	}
	free(gnl_tmp);
	cub3d->file = ft_split(input, '\n');
	free(input);
	return (0);
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
		if (ft_strlen(line) == 0 || is_empty_line(line))
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
	int	fd;

	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL)
		return (3);
	fd = open(filename, O_RDONLY);
	cub()->fd = fd;
	if (cub()->fd < 0)
	{
		if (errno == ENOENT)
		{
			printf("Error, %s does not exist.\n", filename);
			return (1);
		}
		return (2);
	}
	if (get_input(cub()))
		return (5);
	if (parse_textures(cub()))
		return (4);
	return (0);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\n')
			return (false);
	}
	return (true);
}
