#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/include/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> //perror
#include <stdbool.h>
#include "MLX42/MLX42.h"
#define WIDTH 1024
#define HEIGHT 180
#define TILE 64

//add calculation to make grid fit into screen, follow 16:9 ratio

typedef struct s_texture
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*player;
	mlx_texture_t	*collectable;
	mlx_texture_t	*exit;
}t_texture;

typedef struct s_image
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	mlx_image_t	*collectable;
	mlx_image_t	*exit;
}t_image;

typedef struct s_map
{
	int		fd;
	char	*line;
	char	*file_name;;
	char	**grid;
	size_t 	col;
	size_t	row;
	size_t	playerx;
	size_t	playery;
	size_t	collectable;
	size_t	exit;
}t_map;

typedef struct s_gmae
{
	mlx_t		*mlx;
	t_map		*map;
	t_image		*image;
	t_texture	*texture;
	size_t		collectable_count;
}t_game;


int	 ft_isspace(char c);
void open_map(t_map *map);
void init_struct(char *file, t_map *map);
void init_game(t_game *game);

void map_validation(t_map *map);
void check_map(t_map *map);
void check_path(t_map *map);

void render_game(t_game *game);
void collect_item(t_game *game, int dest_y, int dest_x);
void move_player(t_game *game, int dest_x, int dest_y);

void exit_with_msg(char *msg);
void free_map_and_exit(t_map *map, char *msg);
void free_2d_arr(char **arr);
void free_map_and_exit(t_map *map, char *msg);
void free_game(t_game *game);

#endif