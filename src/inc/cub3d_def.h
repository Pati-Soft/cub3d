/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:28 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/30 16:37:13 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEF_H
# define CUB3D_DEF_H

# ifdef __linux__
/* Linux. --------------------------------------------------- */
/*
**  #  include "./linux.h"
** WSL keycodes
*/
#  define MLX_KEY_ESC		65307
#  define MLX_KEY_Q			113

#  define MLX_KEY_W			119
#  define MLX_KEY_A			97
#  define MLX_KEY_S			114
#  define MLX_KEY_D			115

#  define MLX_KEY_LARROW	65361
#  define MLX_KEY_RARROW	65363

# elif __APPLE__
/* OSX. --------------------------------------------------- */
/*
** #  include "./apple.h"
*/

#  define MLX_KEY_ESC			53
#  define MLX_KEY_Q				12

#  define MLX_KEY_W				13
#  define MLX_KEY_A				0
#  define MLX_KEY_S				1
#  define MLX_KEY_D				2

#  define MLX_KEY_LARROW		123
#  define MLX_KEY_RARROW		124

# endif

# define ON_KEYDOWN				2
# define ON_KEYUP				3
# define ON_MOUSEDOWN			4
# define ON_MOUSEUP				5
# define ON_MOUSEMOVE			6
# define ON_EXPOSE				12
# define ON_DESTROY				17

# define ERR_MALLOC				"malloc error\n"
# define ERR_NULL				"null error\n"

# define EXAMPLE_ERR			"followed by an explicit error message, \
	sademir.ber error\n"
# define ERR_EXT_XPM				"Texture file must have .xpm extension\n"
# define ERR_MAP_OPEN 			"Map file cannot be opened\n"
# define ERR_TEX_OPEN 			"Texture file cannot be opened\n"
# define ERR_PREFIX 				"Error\n"
# define ERR_MAP_CORRUPTED 		"corrupted map file\n"
# define ERR_CLOSE_FD			"close fd error\n"
# define ERR_ARGC 				"Usage: ./cub3d <map.cub>\n"
# define ERR_MISSING				"Missing elements in map file\n"
# define ERR_WRONG_DIR			"Wrong direction in map file\n"
# define ERR_KEY					"Wrong key in map file\n"
# define ERR_VALUE				"value does not exist in key\n"
# define ERR_DUP_KEY				"duplicate key\n"
# define ERR_WRONG_COLOR			"Wrong color in map file\n"
# define ERR_NO_SPACE_SEPERATOR	"No space seperator in map file\n"
# define ERR_2MAP				"map 2, 2 map\n"
# define ERR_UNVALIDATABLE		"relative invalid line\n"
# define ERR_UNVALIDATABLE1		"relative invalid line 1\n"
# define ERR_UNVALIDATABLE2		"relative invalid line 2\n"
# define ERR_UNVALIDATABLE3		"relative invalid line 3\n"
# define ERR_UNVALIDATABLE4		"relative invalid line 4\n"
# define ERR_UNVALIDATABLE5		"relative invalid line 5\n"
# define ERR_MULTIPLAYER			"multiplayer dedect\n"
# define ERR_PLAYER				"player not found\n"
# define MAP_EXTENSION			".cub"
# define TEX_EXTENSION			".xpm"

# define WIN_WIDTH				1920
# define WIN_HEIGHT				1080
# define WIN_TITLE				"Cub3D"

# define TEXT_NO				"NO"
# define TEXT_SO				"SO"
# define TEXT_WE				"WE"
# define TEXT_EA				"EA"

# define TEXT_F					"F"
# define TEXT_C					"C"

# define NORTH_CHAR				'N'
# define SOUTH_CHAR				'S'
# define WEST_CHAR				'W'
# define EAST_CHAR				'E'
# define WALL_CHAR				'1'
# define FLOOR_CHAR				'0'

# define RESULATION				16

# define DIR_E					0
# define DIR_N					90
# define DIR_W					180
# define DIR_S					270

# define TOTAL_COUNT			6

# define MOVOMENT_KEY_COUNT		4
# define ROTATION_KEY_COUNT		2

# define KEY_W_IDX				0
# define KEY_A_IDX				1
# define KEY_S_IDX				2
# define KEY_D_IDX				3

# define KEY_LARROW_IDX			4
# define KEY_RARROW_IDX			5

# define ROTATION_SPEED			0.05
# define MOVEMENT_SPEED			0.1

# define FOV					0.44

# ifndef M_PI
#  define M_PI					3.14159265358979323846
# endif

#endif
