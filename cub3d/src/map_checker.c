#include "cub3d.h"

static void is_map_closed(char **map);
static bool is_closed(char **map, t_point p);

void check_map(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i][0] != '1')
		i++;
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
		while (map[i][++j])
		{
			p = (t_point){j, i};
			if (map[i][j] != '1' && !is_closed(map, p))
				program_errors("MAP NOT CLOSED", true, true);
		}
	}
}

static bool is_closed(char **map, t_point p)
{
	if (!map[p.x - 1][p.y])
		return false;
	if (!map[p.x + 1][p.y])
		return false;
	if (!map[p.x][p.y - 1])
		return false;
	if (!map[p.x][p.y + 1])
		return false;
	return true;
}
