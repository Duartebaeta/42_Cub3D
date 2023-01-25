/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:01:54 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/01/25 01:16:49 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_values(char **values)
{
	char	*tmp;
	int		counter;
	int		array_counter;

	array_counter = -1;
	while (values[++array_counter])
	{
		tmp = ft_strtrim(values[array_counter], " ");
		counter = -1;
		while (tmp[++counter])
		{
			if (!ft_isdigit(tmp[counter]) || ft_atoi(tmp) < 0
				|| ft_atoi(tmp) > 255)
			{
				ft_strarray_clear(&values);
				free(tmp);
				return (1);
			}
		}
		free(tmp);
	}
	return (0);
}

static int	assign_values(t_cub3d *cub3d, char **path)
{
	char	**values;
	int		counter;

	values = ft_split(path[1], ',');
	if (array_len(values) != 3)
	{
		ft_strarray_clear(&values);
		return (1);
	}
	if (check_values(values))
		return (2);
	counter = -1;
	if (ft_strncmp("F\0", path[0], 2) == 0)
	{
		while (values[++counter])
			cub3d->floor[counter] = ft_atoi(values[counter]);
	}
	else if (ft_strncmp("C\0", path[0], 2) == 0)
	{
		while (values[++counter])
			cub3d->ceiling[counter] = ft_atoi(values[counter]);
	}
	return (0);
}

static int	check_path(t_cub3d *cub3d, char **path, int counter)
{
	int		fd;

	// TODO: Protect against files with spaces in the name
	if (counter >= 4)
	{
		return (assign_values(cub3d, path));
	}
	else
		return (0);
	if (ft_strnstr(path[1], ".xpm", ft_strlen(path[1])) == NULL)
		return (1);
	fd = open(path[1], O_RDONLY);
	if (fd < 0)
		return (2);
	if (ft_strncmp("NO\0", path[0], 3) == 0)
		cub3d->no->addr = path[1];
	else if (ft_strncmp("SO\0", path[0], 3) == 0)
		cub3d->so->addr = path[1];
	else if (ft_strncmp("WE\0", path[0], 3) == 0)
		cub3d->we->addr = path[1];
	else if (ft_strncmp("EA\0", path[0], 3) == 0)
		cub3d->ea->addr = path[1];
	close(fd);
	return (0);
}

static int	check_coord(char *coord, int c)
{
	static int		*coord_bool;
	char			**textures;
	int				counter;

	if (!coord_bool)
		coord_bool = protected_calloc(6, sizeof(int));
	textures = ft_split("NO SO WE EA F C\0", ' ');
	counter = -1;
	while (++counter < 6)
	{
		if (ft_strncmp(coord, textures[counter], ft_strlen(coord)) == 0
			&& !coord_bool[counter])
		{
			coord_bool[counter] = 1;
			ft_strarray_clear(&textures);
			if (c == 5)
				free(coord_bool);
			return (0);
		}
	}
	ft_strarray_clear(&textures);
	free(coord_bool);
	return (1);
}

static int	parse_textures(t_cub3d *cub3d)
{
	int		counter;
	char	*line;
	char	**split;

	counter = 0;
	while (counter < 6 && cub3d->input)
	{
		line = ft_strtrim(*(cub3d->input), " ");
		if (ft_strlen(line) == 0)
		{
			free(line);
			cub3d->input++;
			continue ;
		}
		else
		{
			split = ft_split(line, ' ');
			free(line);
			if (array_len(split) < 2 || check_coord(split[0], counter))
				break ;
			else if (check_path(cub3d, split, counter))
				break ;
			ft_strarray_clear(&split);
			counter++;
			cub3d->input++;
		}
	}
	if (counter == 6)
		return (0);
	ft_strarray_clear(&split);
	return (1);
}

static void	get_input(t_cub3d *cub3d)
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

int	arg_checker(t_cub3d *cub3d)
{
	if (ft_strnstr(cub3d->filename, ".cub", ft_strlen(cub3d->filename)) == NULL)
		return (3);
	cub3d->fd = open(cub3d->filename, O_RDONLY);
	if (cub3d->fd < 0)
	{
		if (errno == ENOENT)
		{
			printf("Error, %s does not exist.\n", cub3d->filename);
			return (1);
		}
		return (2);
	}
	get_input(cub3d);
	if (parse_textures(cub3d))
		return (1);
	return 0;
}
