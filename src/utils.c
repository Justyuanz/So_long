/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:54:07 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/08 17:44:34 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_texture(t_game *game)
{
	if (!game)
		return ;
	if (game->texture)
	{
		if (game->texture->floor)
			mlx_delete_texture(game->texture->floor);
		if (game->texture->wall)
			mlx_delete_texture(game->texture->wall);
		if (game->texture->player)
			mlx_delete_texture(game->texture->player);
		if (game->texture->collectable)
			mlx_delete_texture(game->texture->collectable);
		if (game->texture->exit)
			mlx_delete_texture(game->texture->exit);
		free(game->texture);
		game->texture = NULL;
	}
}

void	init_struct(char *file, t_map *map)
{
	map->fd = -1;
	map->row = 0;
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
