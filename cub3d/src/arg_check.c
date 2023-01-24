#include "cub3d.h"

static int	check_values(char **values)
{
	char	*tmp;

	while(*values)
	{
		tmp = ft_strtrim(*values, " ");
		while(*tmp)
		{
			if (!ft_isdigit(*tmp))
			{
				ft_strarray_clear(&values);
				free(tmp);
				return (1);
			}
			tmp++;
		}
		free(tmp);
		values++;
	}
	return (0);
}

static int	assign_values(char **path)
{
	char	**values;

	values = ft_split(*path, ',');
	if (array_len(values) != 3)
	{
		ft_strarray_clear(&values);
		return (1);
	}
	if (check_values(values))
		return (2);
	if (ft_strncmp("F\0", path[0], 2) == 0)
		cub()->no->addr = path[1]; //Change to floor and ceiling
	else if (ft_strncmp("C\0", path[0], 2) == 0)
		cub()->so->addr = path[1];
		
	return (0);
}

static int	check_path(t_cub3d *cub3d, char **path, int counter)
{
	int		fd;

	// TODO: Protect against files with spaces in the name
	if (counter >= 4)
		assign_values(path);
	else
		return 0;

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

static int	check_coord(t_cub3d *cub3d, char *coord, int c)
{
	static int		*coord_bool;
	char	**textures;
	int		counter;

	textures = ft_split("NO SO WE EA F C\0", ' ');
	if (!coord_bool)
		coord_bool = protected_calloc(6, sizeof(int));
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
	(void) cub3d;
	return (1);
}

static int	parse_textures(t_cub3d *cub3d)
{
	int		counter;
	char	*line;
	char	**tmp;

	counter = 0;
	while (counter < 6 && cub3d->input)
	{
		line = ft_strtrim(*(cub3d->input), " ");
		if (ft_strlen(line) == 0)
		{
			free(line);
			cub3d->input++;
			continue;
		}
		tmp = ft_split(line, ' ');
		free(line);
		if (array_len(tmp) < 2 || check_coord(cub3d, tmp[0], counter))
			break ;
		else if (check_path(cub3d, tmp, counter) != 0)
			break ;
		ft_strarray_clear(&tmp);
		counter++;
		cub3d->input++;
	}
	if (counter == 6)
		return (0);
	ft_strarray_clear(&tmp);
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
	return (parse_textures(cub3d));
	// if (parse_textures(cub3d))
	// 	return (1);
	// for (size_t i = 0; data->map[i]; i++)
	// {
	// 	printf("%s\n", data->map[i]);
	// }
	return 0;
}
