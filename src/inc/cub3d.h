#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
/* Linux. --------------------------------------------------- */
/*
**  #  include "./linux.h"
** WSL keycodes
*/

# elif __APPLE__
/* OSX. --------------------------------------------------- */
/*
** #  include "./apple.h"
*/
# endif

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#include "mlx.h"

# define    WIN_WIDTH 1920
# define    WIN_HEIGHT 1080
# define    WIN_TITLE "Cub3D"

# define    DIRECTION_N 0
# define    DIRECTION_E 90
# define    DIRECTION_S 180
# define    DIRECTION_W 270

# define    IMAGE_COUNT 4

# define    TEMPLE_MAP {\
		"111111111111111111111111",\
		"100000000011000000000001",\
		"101100000111000000000001",\
		"100100000000000000000001",\
		"111111111011000001110001",\
		"100000000011000001110001",\
		"101100000111000011110001",\
		"100100000000000011110001",\
		"100100000000000011110001",\
		"10010000000W000000000001",\
		"100000000000000000000001",\
		"111111111111111111111111"\
        }

# define   	ON_KEYDOWN 2,
# define   	ON_KEYUP 3,
# define   	ON_MOUSEDOWN 4,
# define   	ON_MOUSEUP 5,
# define   	ON_MOUSEMOVE 6,
# define   	ON_EXPOSE 12,
# define   	ON_DESTROY 17

typedef struct s_player
{
    int x;
    int y;
    int direction; // degree
}	t_player;

typedef struct s_cub3d
{
    void	    *mlx;
    void	    *win_mlx;

    char        **map;
	void		*img[IMAGE_COUNT];

	int			floor_color;
	int			ceiling_color;
	int         map_width;
    int         map_height;
    int         directions[256];
    t_player    player;

}	t_cub3d;

int    destroy_window(t_cub3d *cub3d);
int	init_cub3d(t_cub3d *cub3d);
void    dealloc_cub3d(t_cub3d *cub3d);
int key_trigger(int keycode, t_cub3d *cub3d);

#endif
