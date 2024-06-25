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
# include <math.h>

# include "mlx.h"
# include "libft.h"

# include "cub3d_def.h"

typedef enum e_direction
{
	DEFAULT_DIRECTION,
	NO,
	SO,
	WE,
	EA,
	LAST_DIRECTION,
}	t_direction;

typedef enum e_char_type
{
	NON_SELECT,
	INVALID_CHAR,
	SPACE,
	FRAME,
	SURROUNDABLE,
}	t_char_type;

typedef enum e_color
{
	FLOOR,
	CEILING,
	DEFAULT_COLOR,
}	t_color;

typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;

    int direction; // degree
	int	keys[MOVOMENT_KEY_COUNT + ROTATION_KEY_COUNT];
}	t_player;

typedef struct s_ray
{
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	int			map_x;
	int			map_y;
	int			stepx;
	int			stepy;
	double		sidedistx;
	double		sidedisty;
	int			wall;
	int			side;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			tex_x;
	double		texstep;
	double		texpos;
}	t_ray;

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_cub3d
{
    void	    			*mlx;
    void	    			*win_mlx;

	char * const			map_name;
    char * const * const	map;
    t_list					*map2;

	t_list					*textures_success;
	t_image					textures[IMAGE_COUNT];

	t_image					screen_buffer;
	unsigned int			floor_ceiling[COLOR_COUNT];
	t_ray					ray;
    t_player    			player;

}	t_cub3d;

typedef	struct s_map_init
{
	int         fd;
    char        *buff;
	char		*prev;
    int         cont;
    int         meta_ct;
    char        *trim;
    int         func;
	int         (*parser[3])(t_cub3d * const cub3d, struct s_map_init *map_init);
}	t_map_init;

/* FUNCTIONS */
double deg_to_rad(double degrees);
double rad_to_deg(double radians);

int key_release(int keycode, t_cub3d * const cub3d);
int key_press(int keycode, t_cub3d * const cub3d);
int	ft_player_move(t_cub3d * const cub3d);
void	pm(t_cub3d * const cub3d);
void	init_variable(t_cub3d * const cub3d, int argc, char const *argv[]);
int	loop(void *param);
t_list const *ll_nod(t_list const *node, int index);
char	*ft_strrtrim(char const * const s1, char const * const set);
int	ft_strsome(char *s, int (*f)(unsigned int, char *, void *), void *pass);
size_t  arrlen(void const *arr);
void    free_2d(void *ptr);
int eerr(char const * const msg);
int     ft_isspace(int const c);
int err(char const *msg);
int    destroy_game(t_cub3d * const cub3d);
int	init_cub3d(t_cub3d * const cub3d);
void    dealloc_cub3d(t_cub3d * const cub3d);
int	x_isdigit(unsigned int idx, char *curr, void *param);

#endif
