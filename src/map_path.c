#include "so_long.h"
//find starting position
//make a copy of the map
//flood fill the copy (mark visited)
//check if there's any exit or collectable left

static void map_copy(t_map *copy, t_map *map)
{
	int		x;
	int		y;

	x = 0;
	 copy->grid =ft_calloc((map->row + 1),  sizeof(char *));
	 if(!copy->grid)
	 	free_map_and_exit(map, "calloc failed\n");
	 copy->col = map->col;
	 copy->row = map->row;
	 copy->playerx = map->playerx;
	 copy->playery = map->playery;
	 while (map->grid[x] != NULL)
	 {
		y = 0;
		copy->grid[x] = ft_calloc((map->col + 1), sizeof(char));
		if(!copy->grid)
			free_map_and_exit(map, "calloc failed\n");
		while(map->grid[x][y])
		{
			copy->grid[x][y] = map->grid[x][y];
			y++;
		}
		copy->grid[x][y] = '\0';
		x++;
	 }
	 copy->grid[x] = NULL;
}
static void flood_fill(t_map *copy, size_t x, size_t y)
{
	if(copy->grid[x][y] == '1' || copy->grid[x][y] == 'v')
		return;
	copy->grid[x][y] = 'v';
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x, y + 1);
	flood_fill(copy, x, y - 1);
}
void check_path(t_map *map)
{
	t_map	copy;
	size_t	x;
	size_t	y;

	map_copy(&copy, map);
	flood_fill(&copy, map->playerx, map->playery);
	x = 0;
	while (copy.grid[x] != NULL)
	{
		y = 0;
		while(copy.grid[x][y])
		{
			if (copy.grid[x][y] == 'E' || copy.grid[x][y] == 'C')
				free_map_and_exit(map, "not valid path\n");
			y++;
		}
		x++;
	}
	free_2d_arr(copy.grid);
}
