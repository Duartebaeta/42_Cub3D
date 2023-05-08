/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:09 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/05/08 20:53:38 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"
#include <errno.h>
#include <string.h>

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
		return (3);
	}
	if (check_values(values))
		return (4);
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

static int	check_path(t_cub3d *cub3d, char **path)
{
	int		fd;

	if (ft_strncmp(path[0], "F\0", 2) == 0 || ft_strncmp(path[0], "C\0", 2) == 0)
	{
		return (assign_values(cub3d, path));
	}
	if (ft_strnstr(path[1], ".xpm", ft_strlen(path[1])) == NULL)
		return (1);
	fd = open(path[1], O_RDONLY);
	if (fd < 0)
		return (2);
	if (ft_strncmp("NO\0", path[0], 3) == 0)
		cub3d->no.addr = ft_strdup(path[1]);
	else if (ft_strncmp("SO\0", path[0], 3) == 0)
		cub3d->so.addr = ft_strdup(path[1]);
	else if (ft_strncmp("WE\0", path[0], 3) == 0)
		cub3d->we.addr = ft_strdup(path[1]);
	else if (ft_strncmp("EA\0", path[0], 3) == 0)
		cub3d->ea.addr = ft_strdup(path[1]);
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

int	check_textures(t_cub3d *cub3d, char *line, int counter)
{
	char	**split;

	split = ft_split(line, ' ');
	free(line);
	if (array_len(split) < 2 || check_coord(split[0], counter))
	{
		ft_strarray_clear(&split);
		return (1);
	}
	else if (check_path(cub3d, split))
	{
		printf("\nenter\n");
		ft_strarray_clear(&split);
		return (2);
	}
	ft_strarray_clear(&split);
	return (0);
}
