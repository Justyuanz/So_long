/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:51:28 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/08 18:10:50 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_copy(t_map *copy, t_map *map)
{
	int	x;
	int	y;

	copy->grid = ft_calloc((map->row + 1), sizeof(char *));
	if (!copy->grid)
		free_map_and_exit(map, "calloc failed\n");
	copy->col = map->col;
	copy->row = map->row;
	copy->playerx = map->playerx;
	copy->playery = map->playery;
	x = -1;
	while (map->grid[++x] != NULL)
	{
		y = -1;
		copy->grid[x] = ft_calloc((map->col + 1), sizeof(char));
		if (!copy->grid[x])
		{
			free_2d_arr(copy->grid);
			free_map_and_exit(map, "calloc failed\n");
		}
		while (map->grid[x][++y])
			copy->grid[x][y] = map->grid[x][y];
		copy->grid[x][y] = '\0';
	}
	copy->grid[x] = NULL;
}

static void	flood_fill(t_map *copy, size_t x, size_t y)
{
	if (copy->grid[x][y] == '1' || copy->grid[x][y] == 'v')
		return ;
	copy->grid[x][y] = 'v';
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x, y + 1);
	flood_fill(copy, x, y - 1);
}

void	check_path(t_map *map)
{
	t_map	copy;
	size_t	x;
	size_t	y;

	map_copy(&copy, map);
	flood_fill(&copy, map->playery, map->playerx);
	x = 0;
	while (copy.grid[x] != NULL)
	{
		y = 0;
		while (copy.grid[x][y])
		{
			if (copy.grid[x][y] == 'E' || copy.grid[x][y] == 'C')
			{
				free_2d_arr(copy.grid);
				free_map_and_exit(map, "not valid path\n");
			}
			y++;
		}
		x++;
	}
	free_2d_arr(copy.grid);
	if (TILE * map->col > 4480 || TILE * map->row > 2520)
		free_map_and_exit(map, "map too big\n");
}
