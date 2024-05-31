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
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

#include "mlx.h"
#include "libft.h"

# define	ERR_MALLOC				"malloc error\n"
# define	ERR_NULL				"null error\n"

# define	EXAMPLE_ERR				"followed by an explicit error message :D, sademir.ber \
	error\n"
# define	ERR_EXT_XPM				"Texture file must have .xpm extension\n"
# define	ERR_MAP_OPEN 			"Map file cannot be opened\n"
# define	ERR_TEX_OPEN 			"Texture file cannot be opened\n"
# define	ERR_PREFIX 				"Error\n"
# define	ERR_MAP_CORRUPTED 		"corrupted map file\n"
# define	ERR_CLOSE_FD			"close fd error\n"
# define	ERR_ARGC 				"Usage: ./cub3d <map.cub>\n"
# define	ERR_MISSING				"Missing elements in map file\n"
# define	ERR_WRONG_DIR			"Wrong direction in map file\n"
# define	ERR_WRONG_COLOR			"Wrong color in map file\n"
# define	ERR_NO_SPACE_SEPERATOR	"No space seperator in map file\n"

# define	MAP_EXTENSION ".cub"
# define	TEX_EXTENSION ".xpm"

# define    WIN_WIDTH 1920
# define    WIN_HEIGHT 1080
# define    WIN_TITLE "Cub3D"

# define    TEXT_NO		"NO"
# define    TEXT_SO		"SO"
# define    TEXT_WE		"WE"
# define    TEXT_EA		"EA"

# define    TEXT_F		"F"
# define    TEXT_C		"C"

# define    DIRECTION_N 0
# define    DIRECTION_E 90
# define    DIRECTION_S 180
# define    DIRECTION_W 270

# define    IMAGE_COUNT 4
# define    COLOR_COUNT 2

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

typedef enum e_direction
{
	DEFAULT_DIRECTION,
	NO,
	SO,
	WE,
	EA
}	t_direction;

typedef enum e_color
{
	FLOOR,
	CEILING,
	DEFAULT_COLOR,
}	t_color;

typedef struct s_player
{
    int x;
    int y;
    int direction; // degree
}	t_player;

typedef struct s_cub3d
{
    void	    			*mlx;
    void	    			*win_mlx;

    char * const * const	map;
	void const * const		img[IMAGE_COUNT];

	char const * const		map_name;
	unsigned int						floor_ceiling[COLOR_COUNT];
	int const				texture_w;
	int const				texture_h;
	int const				map_width;
    int const				map_height;
    int const				directions[256];
    t_player    			player;

}	t_cub3d;

typedef	struct s_map_init
{
	int         fd;
    char        *buff;
    int         cont;
    int         meta_ct;
    char        *trim;
    int         func;
	int         (*parser[3])(t_cub3d * const cub3d, struct s_map_init *map_init);
}	t_map_init;

size_t  arrlen(void **arr);
void    free_2d(void **ptr);
int eerr(char *msg);
int     ft_isspace(int c);
int err(char *msg);
int    destroy_window(t_cub3d * const cub3d);
int	init_cub3d(t_cub3d * const cub3d);
void    dealloc_cub3d(t_cub3d * const cub3d);
int key_trigger(int keycode, t_cub3d * const cub3d);

#endif
