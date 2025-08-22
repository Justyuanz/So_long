#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/include/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> //perror

typedef struct s_map
{
	int		fd;
	char	*line;
	char	*append_line;
}t_map;

int	ft_isspace(char c);
void	init_struct(t_map *map);

#endif