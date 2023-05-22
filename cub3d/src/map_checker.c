/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <jocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:46:06 by jocaetan          #+#    #+#             */
/*   Updated: 2023/05/22 17:10:10 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_map_closed(char **map);
static bool	is_closed(char **map, t_point p, int max_x, int max_y);
static bool	check_map_edges(char **map, t_point p, int max_x, int max_y);
static bool	is_map_char(char c);

void	check_map(void)
{
	create_map_from_file(cub());
	is_map_closed(cub()->map);
}

void	is_map_closed(char **map)
{
	int	i;
	int	j;
	int	max_y;
	int	max_x;

	i = -1;
	max_y = ft_strarray_len(map);
	while (++i < max_y)
	{
		j = -1;
		printf("%s\n", map[i]);
		max_x = ft_strlen(map[i]);
		while (map[i][++j])
		{
			if (!(map[i][j] == '1' || ft_isspace(map[i][j]))
				&& !is_closed(map, (t_point){j, i, 0}, max_x, max_y))
				program_errors("Map not closed", true, true);
		}
	}
}

static bool	is_closed(char **map, t_point p, int max_x, int max_y)
{
	int	adjacent;

	errno = ENOEXEC;
	adjacent = 0;
	if (p.x == 0 || p.y == 0 || p.x == 0 || p.x == max_x - 1)
		return (check_map_edges(map, p, max_x, max_y));
	else
	{
		if (map[p.y - 1][p.x] && is_map_char(map[p.y - 1][p.x])
			&& map[p.y - 1][p.x - 1] && is_map_char(map[p.y - 1][p.x - 1])
			&& map[p.y - 1][p.x + 1] && is_map_char(map[p.y - 1][p.x + 1]))
			adjacent++;
		if (map[p.y + 1] && map[p.y + 1][p.x] && is_map_char(map[p.y + 1][p.x])
			&& map[p.y + 1][p.x - 1] && is_map_char(map[p.y + 1][p.x - 1])
			&& map[p.y + 1][p.x + 1] && is_map_char(map[p.y + 1][p.x + 1]))
			adjacent++;
		if (map[p.y][p.x - 1] && is_map_char(map[p.y][p.x - 1]))
			adjacent++;
		if (map[p.y][p.x + 1] && is_map_char(map[p.y][p.x + 1]))
			adjacent++;
		if (adjacent == 4)
			return (true);
	}
	return (false);
}

static bool	check_map_edges(char **map, t_point p, int max_x, int max_y)
{
	if (p.y == 0 && (map[p.y][p.x] == '1' || ft_isspace(map[p.y][p.x])))
		return (true);
	if (p.y == max_y && (map[p.y][p.x] == '1' || ft_isspace(map[p.y][p.x])))
		return (true);
	if (p.x == 0 && (map[p.y][p.x] == '1' || ft_isspace(map[max_y - 1][p.x])))
		return (true);
	if (p.x == max_x - 1 && (map[p.y][p.x] == '1' || ft_isspace(map[p.y][p.x])))
		return (true);
	return (false);
}

static bool	is_map_char(char c)
{
	if (c && !ft_isspace(c))
		return (true);
	return (false);
}
