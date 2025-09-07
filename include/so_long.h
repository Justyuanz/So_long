/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:47:37 by jinzhang          #+#    #+#             */
/*   Updated: 2025/09/07 20:52:05 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../libft/include/libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h> //perror
# include <stdlib.h>
# define WIDTH 1024
# define HEIGHT 180
# define TILE 64

typedef struct s_texture
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*player;
	mlx_texture_t	*collectable;
	mlx_texture_t	*exit;
}					t_texture;

typedef struct s_image
{
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*player;
	mlx_image_t		*collectable;
	mlx_image_t		*exit;
}					t_image;

typedef struct s_map
{
	int				fd;
	char			*line;
	char			*file_name;
	char			**grid;
	size_t			col;
	size_t			row;
	size_t			playerx;
	size_t			playery;
	size_t			collectable;
	size_t			exit;
}					t_map;

typedef struct s_gmae
{
	mlx_t			*mlx;
	t_map			*map;
	t_image			*image;
	t_texture		*texture;
	size_t			collectable_count;
	int				player_move;
}					t_game;

int					ft_isspace(char c);
void				open_map(t_map *map);
void				init_struct(char *file, t_map *map);
void				init_game(t_game *game);

void				map_validation(t_map *map);
void				check_map(t_map *map);
void				check_path(t_map *map);

void				render_game(t_game *game);
void				key_hook(mlx_key_data_t keydata, void *param);
void				draw_map(t_game *game);
bool				draw_image(t_game *game, int x, int y);

void				exit_with_msg(char *msg);
void				free_map_and_exit(t_map *map, char *msg);
void				free_2d_arr(char **arr);
void				free_map_and_exit(t_map *map, char *msg);
void				free_game(t_game *game);

#endif
