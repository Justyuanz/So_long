/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:49:02 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/07 20:49:38 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	check_map_rectangular(t_map *map)
{
	int	x;

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

static bool	check_charset(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (map->grid[x] != NULL)
	{
		y = 0;
		while (y < ft_strlen(map->grid[0]))
		{
			if (map->grid[x][y] != '0' && map->grid[x][y] != '1'
				&& map->grid[x][y] != 'C' && map->grid[x][y] != 'E'
				&& map->grid[x][y] != 'P')
				return (false);
			y++;
		}
		x++;
	}
	return (true);
}

static bool	element_vaidation(t_map *map)
{
	size_t	x;
	size_t	y;
	int		start_position;

	start_position = 0;
	x = -1;
	while (map->grid[++x] != NULL)
	{
		y = -1;
		while (++y < (ft_strlen(map->grid[0])))
		{
			if (map->grid[x][y] == 'C')
				map->collectable++;
			if (map->grid[x][y] == 'E')
				map->exit++;
			if (map->grid[x][y] == 'P')
			{
				start_position++;
				map->playerx = y;
				map->playery = x;
			}
		}
	}
	return (map->collectable >= 1 && map->exit == 1 && start_position == 1);
}

static bool	check_walls(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	strlen;

	x = 0;
	y = 0;
	strlen = ft_strlen(map->grid[0]);
	while (map->grid[x] != NULL)
	{
		y = 0;
		while (y < strlen)
		{
			if (map->grid[0][y] != '1' || map->grid[map->row - 1][y] != '1')
				return (false);
			else if (map->grid[x][0] != '1' || map->grid[x][strlen - 1] != '1')
				return (false);
			y++;
		}
		x++;
	}
	return (true);
}

void	check_map(t_map *map)
{
	if (!check_map_rectangular(map))
		free_map_and_exit(map, "map is not rectangular\n");
	if (!check_charset(map))
		free_map_and_exit(map, "invalid charset\n");
	if (!element_vaidation(map))
		free_map_and_exit(map, "invalid amount of element\n");
	if (!check_walls(map))
		free_map_and_exit(map, "map is not surrounded by walls\n");
}
