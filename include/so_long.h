#ifndef SO_LONG_H
# define SO_LONG_H

#include "../libft/include/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> //perror

typedef struct s_so_long
{
	int	fd;
	char	*line;
}t_so_long;

int	ft_isspace(char c);
void	init_struct(t_so_long *map);

#endif