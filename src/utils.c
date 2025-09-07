/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:54:07 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/07 20:54:45 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_struct(char *file, t_map *map)
{
	map->fd = -1;
	map->row = 0;
	map->grid = NULL;
	map->playerx = -1;
	map->playery = -1;
	map->collectable = 0;
	map->exit = 0;
	map->file_name = file;
}

void	init_game(t_game *game)
{
	game->collectable_count = game->map->collectable;
	game->player_move = 0;
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

void	open_map(t_map *map)
{
	map->fd = open(map->file_name, O_RDONLY);
	if (map->fd == -1)
		exit_with_msg("file open error\n");
}
