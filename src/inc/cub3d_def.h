#ifndef CUB3D_DEF_H
# define CUB3D_DEF_H

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
# define	ERR_2MAP				"map 2, 2 map\n"
# define	ERR_UNVALIDATABLE		"relative invalid line\n"
# define	ERR_UNVALIDATABLE1		"relative invalid line 1\n"
# define	ERR_UNVALIDATABLE2		"relative invalid line 2\n"
# define	ERR_UNVALIDATABLE3		"relative invalid line 3\n"
# define	ERR_UNVALIDATABLE4		"relative invalid line 4\n"
# define	ERR_UNVALIDATABLE5		"relative invalid line 5\n"
# define	ERR_MULTIPLAYER			"multiplayer dedect\n"

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

#endif
