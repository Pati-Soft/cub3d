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
}	t_player;

typedef struct s_cub3d
{
    void	    			*mlx;
    void	    			*win_mlx;

    char * const * const	map;
    t_list					*map2;
	void const * const		img[IMAGE_COUNT];

	char const * const		map_name;
	unsigned int			floor_ceiling[COLOR_COUNT];
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
	char		*prev;
    int         cont;
    int         meta_ct;
    char        *trim;
    int         func;
	int         (*parser[3])(t_cub3d * const cub3d, struct s_map_init *map_init);
}	t_map_init;

/* FUNCTIONS */
int	loop(void *param);
t_list	*ll_nod(t_list *node, int index);
char	*ft_strrtrim(char const *s1, char const *set);
int	ft_strsome(char *s, int (*f)(unsigned int, char *, void *), void *pass);
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
