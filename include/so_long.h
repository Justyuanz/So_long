#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/include/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> //perror
#include <stdbool.h>

typedef struct s_map
{
	int		fd;
	size_t 	col;
	size_t	row;
	size_t	playerx;
	size_t	playery;
	char	*line;
	char	*file_name;;
	char	**grid;
}t_map;

int	ft_isspace(char c);
void	init_struct(char *file, t_map *map);
bool check_map(t_map *map);
bool check_path(t_map *map);

#endif