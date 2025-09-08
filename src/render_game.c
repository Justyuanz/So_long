/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:53:45 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/08 11:20:57 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	draw_image(t_game *game, int x, int y)
{
	if (mlx_image_to_window(game->mlx, game->image->floor, y * TILE, x
			* TILE) < 0)
		return (false);
	if (game->map->grid[x][y] == '1')
	{
		if (mlx_image_to_window(game->mlx, game->image->wall, y * TILE, x
				* TILE) < 0)
			return (false);
	}
	else if (game->map->grid[x][y] == 'C')
	{
		if (mlx_image_to_window(game->mlx, game->image->collectable, y * TILE, x
				* TILE) < 0)
			return (false);
	}
	else if (game->map->grid[x][y] == 'E')
	{
		if (mlx_image_to_window(game->mlx, game->image->exit, y * TILE, x
				* TILE) < 0)
			return (false);
		game->image->exit->instances[0].enabled = false;
	}
	return (true);
}

static void	resize_image(t_game *game)
{
	mlx_delete_texture(game->texture->floor);
	mlx_delete_texture(game->texture->wall);
	mlx_delete_texture(game->texture->player);
	mlx_delete_texture(game->texture->collectable);
	mlx_delete_texture(game->texture->exit);
	free(game->texture);
	game->texture = NULL;
	mlx_resize_image(game->image->floor, TILE, TILE);
	mlx_resize_image(game->image->wall, TILE, TILE);
	mlx_resize_image(game->image->player, TILE, TILE);
	mlx_resize_image(game->image->collectable, TILE * 0.8, TILE * 0.8);
	mlx_resize_image(game->image->exit, TILE, TILE);
}

static bool	convert_image(t_game *game)
{
	game->image = ft_calloc(1, sizeof(t_image));
	game->image->floor = mlx_texture_to_image(game->mlx, game->texture->floor);
	game->image->player = mlx_texture_to_image(game->mlx,
			game->texture->player);
	game->image->wall = mlx_texture_to_image(game->mlx, game->texture->wall);
	game->image->collectable = mlx_texture_to_image(game->mlx,
			game->texture->collectable);
	game->image->exit = mlx_texture_to_image(game->mlx, game->texture->exit);
	if (!game->image->floor || !game->image->wall || !game->image->player
		|| !game->image->collectable || !game->image->exit)
		return (false);
	resize_image(game);
	return (true);
}

static bool	load_texture(t_game *game)
{
	game->texture = ft_calloc(1, sizeof(t_texture));
	if (!game->texture)
		free_map_and_exit(game->map, "texture calloc fail\n");
	game->texture->floor = mlx_load_png("images/floor.png");
	game->texture->wall = mlx_load_png("images/wall.png");
	game->texture->player = mlx_load_png("images/sprite.png");
	game->texture->collectable = mlx_load_png("images/collectable1.png");
	game->texture->exit = mlx_load_png("images/exit.png");
	if (!game->texture->floor || !game->texture->wall || !game->texture->player
		|| !game->texture->collectable || !game->texture->exit)
		return (false);
	return (true);
}

void	render_game(t_game *game)
{
	init_game(game);
	if (!game)
	{
		free_game(game);
		exit_with_msg("Error init game\n");
	}
	if (!load_texture(game))
	{
		free_game(game);
		exit_with_msg("Error loading texture\n");
	}
	game->mlx = mlx_init(TILE * game->map->col, TILE * game->map->row,
			"SO_LONG", true);
	if (!game->mlx)
	{
		free_game(game);
		exit_with_msg("Error init mlx\n");
	}
	if (!convert_image(game))
	{
		free_game(game);
		exit_with_msg("Error load textures\n");
	}
	draw_map(game);
	mlx_key_hook(game->mlx, &key_hook, game);
}
