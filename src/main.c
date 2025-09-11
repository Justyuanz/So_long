/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:51:11 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/08 17:06:19 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2)
		exit_with_msg("Error\n");
	ft_bzero(&map, sizeof(map));
	init_struct(argv[1], &map);
	map_validation(&map);
	ft_bzero(&game, sizeof(game));
	game.map = &map;
	render_game(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
