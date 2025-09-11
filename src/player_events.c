/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:52:35 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/08 18:06:31 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map->grid[x] != NULL)
	{
		y = 0;
		while (game->map->grid[x][y])
		{
			if (!draw_image(game, x, y))
			{
				free_game(game);
				exit_with_msg("Error drawing image\n");
			}
			y++;
		}
		x++;
	}
	if (mlx_image_to_window(game->mlx, game->image->player, game->map->playerx
			* TILE, game->map->playery * TILE) < 0)
	{
		free_game(game);
		exit_with_msg("Error drawing image\n");
	}
}

static void	collect_item(t_game *game, int dest_y, int dest_x)
{
	size_t	i;

	i = 0;
	while (i < game->collectable_count)
	{
		if (game->image->collectable->instances[i].x == dest_x * TILE
			&& game->image->collectable->instances[i].y == dest_y * TILE)
		{
			if (game->image->collectable->instances[i].enabled == true)
				game->map->collectable--;
			game->image->collectable->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

static void	move_player(t_game *game, int dest_x, int dest_y)
{
	char	position;

	position = game->map->grid[dest_y][dest_x];
	if (position == '1')
		return ;
	game->map->playerx = dest_x;
	game->map->playery = dest_y;
	game->image->player->instances[0].x = dest_x * TILE;
	game->image->player->instances[0].y = dest_y * TILE;
	game->player_move++;
	ft_putstr_fd("Move: ", 1);
	ft_putnbr_fd(game->player_move, 1);
	ft_putchar_fd('\n', 1);
	if (position == 'C')
		collect_item(game, dest_y, dest_x);
	if (game->map->collectable == 0)
		game->image->exit->instances[0].enabled = true;
	if (game->map->collectable == 0 && position == 'E')
	{
		ft_putstr_fd("YAYY YOU WIN!", 1);
		mlx_close_window(game->mlx);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = param;
	x = game->map->playerx;
	y = game->map->playery;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(game, x, y - 1);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(game, x, y + 1);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(game, x - 1, y);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(game, x + 1, y);
}
