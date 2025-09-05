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
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit;
}t_texture;

typedef struct s_image
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
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
}t_map;

typedef struct s_gmae
{
	mlx_t		*mlx;
	t_map		*map;
	t_image		*image;
	t_texture	*texture;
}t_game;


int	ft_isspace(char c);
void	init_struct(char *file, t_map *map);
void check_map(t_map *map);
void check_path(t_map *map);
void render_game(t_game *game);

#endif