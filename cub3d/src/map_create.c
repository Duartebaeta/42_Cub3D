#include "cub3d.h"

static char *replace_tab_to_spaces(char *line);
static char **reformat_map(char **map, int max_x);

void create_map_from_file()
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
		}
	}
	cub()->map = reformat_map(map, max_x);
}

static char *replace_tab_to_spaces(char *line)
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

static char **reformat_map(char **map, int max_x)
{
	int		y;
	int		len;
	char	*spaces;
	char	*result;

	y = -1;
	while(map[++y])
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
	return (map);
}
