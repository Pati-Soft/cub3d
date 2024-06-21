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
	EA
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
    int x;
    int y;
    int direction; // degree
	int	keys[MOVOMENT_KEY_COUNT + ROTATION_KEY_COUNT];
}	t_player;

typedef struct s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
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
	int			user_x;
	int			user_y;
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

    char * const * const	map;
    t_list					*map2;

	t_image					textures[IMAGE_COUNT];
	t_image					screen_buffer;
	char const * const		map_name;
	unsigned int			floor_ceiling[COLOR_COUNT];
	int const				map_width;
    int const				map_height;
    int const				directions[256];
	int const				screen_x;
	int const				screen_y;
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
int key_release(int keycode, t_cub3d *cub3d);
int key_press(int keycode, t_cub3d *cub3d);
int	ft_player_move(t_cub3d *cub3d);
void	pm(t_cub3d *cub3d);
void	zeroer(t_cub3d *cub3d);
int	loop(void *param);
t_list	*ll_nod(t_list *node, int index);
char	*ft_strrtrim(char const *s1, char const *set);
int	ft_strsome(char *s, int (*f)(unsigned int, char *, void *), void *pass);
size_t  arrlen(void *arr);
void    free_2d(void *ptr);
int eerr(char *msg);
int     ft_isspace(int c);
int err(char *msg);
int    destroy_window(t_cub3d * const cub3d);
int	init_cub3d(t_cub3d * const cub3d);
void    dealloc_cub3d(t_cub3d * const cub3d);
int key_trigger(int keycode, t_cub3d *const cub3d);

#endif
