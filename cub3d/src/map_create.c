/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:30:02 by dhomem-d          #+#    #+#             */
/*   Updated: 2023/06/15 21:46:27 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**reformat_map(char **map, int max_x);
static void	set_player(int x, int y, char cardinal,
				t_cub3d *cub3d); //thank you norminette

void	create_map_from_file(t_cub3d *cub3d)
{
	char	**map;
	int		x;
	int		y;
	int		max_x;

	map = ft_strarray_dup(&cub()->file[6]);
	max_x = 0;
	y = -1;
	while (map[++y])
	{
		map[y] = replace_tab_to_spaces(map[y]);
		x = -1;
		while (map[y][++x])
		{
			if (x > max_x)
				max_x = x;
			if (ft_strchr("NSEW", map[y][x]))
				set_player(x, y, map[y][x], cub3d);
		}
	}
	cub3d->map = reformat_map(map, max_x);
	cub3d->map[(int)cub3d->player.y][(int)cub3d->player.x] = '0';
}

char	*replace_tab_to_spaces(char *line)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	int		x;

	x = -1;
	while (line[++x])
	{
		if (line[x] == '\t')
		{
			prefix = ft_substr(line, 0, x);
			suffix = ft_substr(line, x + 1, ft_strlen(line));
			temp = ft_strjoin(prefix, "    ");
			line = ft_strjoin(temp, suffix);
			ft_strdel(&prefix);
			ft_strdel(&suffix);
			ft_strdel(&temp);
		}
	}
	temp = ft_strdup(line);
	ft_strdel(&line);
	return (temp);
}

static char	**reformat_map(char **map, int max_x)
{
	int		y;
	int		len;
	char	*spaces;
	char	*result;

	y = -1;
	while (map[++y])
	{
		len = ft_strlen(map[y]);
		if (len < max_x)
		{
			spaces = protected_calloc(max_x - len + 1, sizeof(char));
			spaces = ft_memset(spaces, ' ', max_x - len);
			spaces[max_x - len] = '\0';
			result = ft_strjoin(map[y], spaces);
			ft_strdel(&spaces);
			ft_strdel(&map[y]);
			map[y] = result;
		}
	}
	cub()->map_x = max_x;
	cub()->map_y = y;
	return (map);
}

static void	set_player(int x, int y, char cardinal, t_cub3d *cub3d)
{
	cub3d->player.x = (double)x;
	cub3d->player.y = (double)y;
	if (cardinal == 'E')
		cub3d->player.angle = to_radian(0);
	else if (cardinal == 'W')
		cub3d->player.angle = M_PI;
	else if (cardinal == 'N')
		cub3d->player.angle = -M_PI / 2;
	else if (cardinal == 'S')
		cub3d->player.angle = M_PI / 2;
}
