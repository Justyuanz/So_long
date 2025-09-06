#include "so_long.h"

static bool check_map_rectangular(t_map *map)
{
	int x;

	x = 1;
	if (map->row <= 1)
		free_map_and_exit(map, "map less than 1 row\n");
	map->col = ft_strlen(map->grid[0]);
	while (map->grid[x] != NULL)
	{
		if (map->col != (ft_strlen(map->grid[x])))
			return (false);
		x++;
	}
	return (true);
}
static bool check_charset(t_map *map)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	while (map->grid[x] != NULL)
	{
		y = 0;
		while ( y < ft_strlen(map->grid[0]))
		{
			if (map->grid[x][y] != '0' && map->grid[x][y] != '1'
				&& map->grid[x][y] != 'C' && map->grid[x][y] != 'E' &&
				map->grid[x][y] != 'P')
				return (false);
			y++;
		}
		x++;
	}
	return (true);
}
static bool element_vaidation(t_map *map)
{
	size_t x;
	size_t y;
	int	start_position;

	start_position = 0;
	x = 0;
	while (map->grid[x] != NULL)
	{
		y = 0;
		while (y < (ft_strlen(map->grid[0])))
		{
			if (map->grid[x][y] == 'C')
				map->collectable++;
			if(map->grid[x][y] == 'E')
				map->exit++;
			if(map->grid[x][y] == 'P')
			{
				start_position++;
				map->playerx = y;
				map->playery = x;
			}
			y++;
		}
		x++;
	}
	if (map->collectable >= 1 && map->exit == 1 && start_position == 1)
		return (true);
	return (false);
}
static bool check_walls(t_map *map)
{
	size_t x;
	size_t y;
	size_t strlen;

	x = 0;
	y = 0;
	strlen = ft_strlen(map->grid[0]);
	while (map->grid[x] != NULL)
	{
		y = 0;
		while ( y < strlen)
		{
			if (map->grid[0][y] != '1' || map->grid[map->row - 1][y] != '1')
				return (false);
			 else if (map->grid[x][0] != '1' || map->grid[x][strlen-1] != '1')
				return (false);
			y++;
		}
		x++;
	}
	return (true);
}

void check_map(t_map *map) //need to do safe exits in this function
{
	if (!check_map_rectangular(map))
		free_map_and_exit(map, "map is not rectangular\n");
	if (!check_charset(map))
		free_map_and_exit(map,"invalid charset\n");
	if (!element_vaidation(map))
		free_map_and_exit(map,"invalid amount of element\n");
	if (!check_walls(map))
		free_map_and_exit(map,"map is not surrounded by walls\n");
}
/*need to (read) map content
1:width should be >1
2:flag for each character, at least each of them
3:height > 1

0 for an empty space,
1 for a wall,
C for a map->collectable,
E for a map exit,
P for the player’s starting position.


The map must be rectangular.
The map must be enclosed/surrounded by walls. If it is not, the program must
return an error.
• You must verify if there is a valid path in the map.
You must be able to parse any kind of map, as long as it respects the above rules.
• Another example of a minimal .ber map:
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
• If any misconfiguration is encountered in the file, the program must exit cleanly,
and return "Error\n" followed by an explicit error message of your choice.
*/

