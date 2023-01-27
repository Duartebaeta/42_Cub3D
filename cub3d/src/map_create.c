#include "cub3d.h"

void create_map_from_file()
{
	char **map;
	int		x;
	int		max_x;
	int		max_y;

	map = ft_strarray_dup(&cub()->file[6]);
	max_x = 0;
	max_y = -1;
	while (map[++max_y])
	{
		map[max_y] = replace_tab_to_spaces(map[max_y]);
		x = -1;
		while (map[max_y][++x])
		{
			if (x > max_x)
				max_x = x;
		}
	}
	cub()->map = reformat_map(map, max_x, max_y);
}

char *replace_tab_to_spaces(char *line)
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

char **reformat_map(char **map, int max_x, int max_y)
{

}
