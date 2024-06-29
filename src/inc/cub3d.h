/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:25 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 16:30:52 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef enum e_types
{
	IMAGE,
	COLOR,
	TYPES_COUNT
}	t_types;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	IMAGE_COUNT,
}	t_direction;

typedef enum e_color
{
	FLOOR,
	CEILING,
	COLOR_COUNT,
}	t_color;

typedef enum e_key
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	KEY_END,
}	t_key;

typedef enum e_return
{
	SUCCESS,
	FAILURE,
}	t_return;
typedef enum e_char_type
{
	NON_SELECT,
	INVALID_CHAR,
	SPACE	,
	FRAME,
	SURROUNDABLE,
}	t_char_type;

typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;

	int			direction;
	int			keys[MOVOMENT_KEY_COUNT + ROTATION_KEY_COUNT];
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
}	t_image;

typedef struct s_cub3d
{
	void					*mlx;
	void					*win_mlx;

	char *const				map_name;
	char *const *const		map;
	t_list					*map2;

	int						resulation;

	t_list					*textures_success;
	t_image					textures[IMAGE_COUNT];

	t_image					screen_buffer;
	unsigned int			gradient[COLOR_COUNT];
	t_ray					ray;
	t_player				player;

}	t_cub3d;

typedef struct s_map_init
{
	int			fd;
	char		*buff;
	char		*prev;
	int			cont;
	int			meta_ct;
	char		*trim;
	t_key		key;
	char		*trim_value;
	int			lengths_key[IMAGE_COUNT + COLOR_COUNT];
	int			match_index[IMAGE_COUNT + COLOR_COUNT];
	int			match_types[IMAGE_COUNT + COLOR_COUNT];
	int			override[IMAGE_COUNT + COLOR_COUNT];
	t_return	(*meta_funcs[2])(t_cub3d * const cub3d,
		struct s_map_init * const map_init);
}	t_map_init;

/* FUNCTIONS */

/*	UTILS */
/*		MATH */
double		deg_to_rad(double degrees);
double		rad_to_deg(double radians);
/*		EXTRAS */
t_return	err(char const *msg);
t_return	eerr(char const*const msg);
int			open2(char const*const path, int const flags, int *const fd);
char		*ft_strrtrim(char const*const s1, char const*const set);
int			ft_strsome(char *s,
				int (*f)(unsigned int, char *, void *), void *pass);
t_list		*ll_nod(t_list const *node, int index);
int			x_isdigit(unsigned int idx, char *curr, void *param);
int			ft_isspace(int const c);
size_t		arrlen(void const *arr);
void		free_2d(void *ptr);
void		close_err(int const fd);
void		void_fun(void *content);
void		pm(t_cub3d *const cub3d);

/*	RENDER */
/*		0 */
void		ft_direction(t_cub3d *const cub3d, int const x);
void		ft_wallhit(t_cub3d *const cub3d, int const x);
void		ft_raydist(t_cub3d *const cub3d, int const x);
void		ft_send_ray(t_cub3d *const cub3d, int const x);
void		ft_ray_casting(t_cub3d *const cub3d);
/*		1 */
void		ft_fill_floor_and_ceiling(t_cub3d *const cub3d);
void		ft_draw_wall_texture(t_cub3d *const cub3d, int const x,
				int const tex_index);
void		ft_texture_helper(t_cub3d *const cub3d);
void		ft_draw_wall_side(t_cub3d *const cub3d, int const x);

/*	HOOKS */
int			key_press(int const keycode, t_cub3d *const cub3d);
int			key_release(int const keycode, t_cub3d *const cub3d);
/*		LOOP */
int			loop(void *const param);
int			ft_player_move(t_cub3d *const cub3d);
void		ft_move(t_cub3d *const cub3d);
/*		ROTATE */
void		key_left(t_cub3d *const cub3d);
void		key_right(t_cub3d *const cub3d);
/*		MOVE */
int			is_character(char const c);
void		key_w(t_cub3d *const cub3d);
void		key_a(t_cub3d *const cub3d);
void		key_s(t_cub3d *const cub3d);
void		key_d(t_cub3d *const cub3d);
/*		DESTROY */
int			destroy_game(t_cub3d *const cub3d);
void		destroy_the_textures(t_cub3d *const cub3d);
void		destroy_map(t_list *map);
void		dealloc_cub3d(t_cub3d *const cub3d);

/*	INIT */
int			loop_meta_info(t_map_init *const map_init, t_cub3d *const cub3d);
int			loop_map(t_map_init *const map_init, t_cub3d *const cub3d);
void		init_variable(t_cub3d *const cub3d, int argc, char const *argv[]);
void		init_struct(t_map_init *dest);
int			map_init(t_cub3d *const cub3d);
int			skip_empty_line(t_map_init *const map_init);
int			check_extension(char const*const path, char const*const ext);
t_key		get_key(char const*const buff);
int			init_cub3d(t_cub3d *const cub3d);
/*		MLX */
void		hook_init(t_cub3d *const cub3d);
int			screen_buffer_init(t_cub3d *const cub3d,
				int screen_x, int screen_y);
int			init_mlx(t_cub3d *const cub3d);
/*		MAP */
int			loop_map(t_map_init *const map_init, t_cub3d *const cub3d);
void		clear_map(t_cub3d *const cub3d);
int			check_relative(const size_t prev_len, char const*const row,
				char const*const prev, size_t const i);
int			player_detected(t_cub3d *const cub3d, char *const row, size_t i);
int			validate_row_mid(char *const row, char *const prev,
				t_cub3d *const cub3d);
int			validate_mid(t_map_init *const map_init, t_cub3d *const cub3d);
int			is_surroundable_char(unsigned int idx, char *c, void *p);
int			validate_top_char(unsigned int idx, char *c, void *p);
int			validate_edge_char(char const*const row);
int			validate_row_top(char *const row);
t_char_type	get_char_type(char const c);
/*		META */
int			loop_meta_info(t_map_init *const map_init, t_cub3d *const cub3d);
int			set_value(t_cub3d *const cub3d, t_map_init *const map_init);
int			set_rgb(char const*const buff, unsigned int *const color);
t_return	set_color(t_cub3d *const cub3d, t_map_init *const map_init);
int			load_texture(t_cub3d *const cub3d, char *const path,
				t_direction const key);
t_return	set_texture(t_cub3d *const cub3d, t_map_init *const map_init);

#endif
