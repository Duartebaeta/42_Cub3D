#include "cub3d.h"

static void is_map_closed(char **map);
static bool is_closed(char **map, t_point p);
static bool is_map_char(char c);

void check_map(t_data *data)
{
	// int i;

	// i = 0;
	// while (data->map[i][0] != '1')
	// 	i++;
	cub()->map = create_map_from_file(data->map);
	data->map1 = &data->map[i];
	is_map_closed(data->map1);
}

void is_map_closed(char **map)
{
	int i;
	int j;
	t_point p;

	i = -1;
	while (map[++i])
	{
		j = -1;
		printf("%s\n", map[i]);
		while (map[i][++j])
		{
			p = (t_point){j, i};
			if (!(map[i][j] == '1' || ft_isspace(map[i][j]))&& !is_closed(map, p))
				program_errors("Map not closed", true, true);
		}
	}
}

static bool is_closed(char **map, t_point p)
{
	int adjacent;

	errno = ENOEXEC;
	adjacent = 0;
	if (is_map_char(map[p.y - 1][p.x]))
		adjacent++;
	if (is_map_char(map[p.y + 1][p.x]))
		adjacent++;
	if (is_map_char(map[p.y][p.x - 1]))
		adjacent++;
	if (is_map_char(map[p.y][p.x + 1]))
		adjacent++;
	if (adjacent == 4)
		return (true);
	return (false);
}

static bool is_map_char(char c)
{
	if (c && !ft_isspace(c))
		return (true);
	return (false);
}