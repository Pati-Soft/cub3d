#include "cub3d.h"

t_direction get_direction(char const * const buff)
{
	if (!ft_strncmp(TEXT_NO, buff, 2))
		return NO;
	if (!ft_strncmp(TEXT_SO, buff, 2))
		return SO;
	if (!ft_strncmp(TEXT_WE, buff, 2))
		return WE;
	if (!ft_strncmp(TEXT_EA, buff, 2))
		return EA;
	return DEFAULT_DIRECTION;
}

t_color get_color(char const * const buff)
{
	if (!ft_strncmp(TEXT_F, buff, 1))
		return FLOOR;
	if (!ft_strncmp(TEXT_C, buff, 1))
		return CEILING;
	return DEFAULT_COLOR;
}

int check_extension(char const * const path, char const * const ext)
{
	if (ft_strlen(path) < 4 || ft_strncmp(ext,
			path + (ft_strlen(path) - 4), 4))
		return (1);
	return (0);
}

void    close_err(int const fd)
{
	if (close(fd) == -1)
		eerr(ERR_CLOSE_FD);
}

// cause `if ((fd = open(path, flags)) == -1)` is forbidden
int open2(char const * const path, int const flags, int * const fd)
{
	*fd = open(path, flags);
	if (*fd == -1)
		return (1);
	return 0;
}

int     set_rgb(char const * const buff, unsigned int * const color)
{
	char	**split = ft_split(buff, ',');
	int		arr[3];
	
	if (!split)
		return (1);
	if (arrlen(split) != 3)
		return (free_2d(split), 1);
	if (ft_strsome(split[0], x_isdigit, NULL) || \
		ft_strsome(split[1], x_isdigit, NULL) || \
		ft_strsome(split[2], x_isdigit, NULL))
		return (free_2d(split), 1);
	arr[0] = ft_atoi(split[0]);
	arr[1] = ft_atoi(split[1]);
	arr[2] = ft_atoi(split[2]);
	free_2d(split);
	if (arr[0] > 255 || arr[1] > 255 || arr[2] > 255 || \
		arr[0] < 0 || arr[1] < 0 || arr[2] < 0)
		return (1);
	return (*color = (arr[0] << 16) | (arr[1] << 8) | (arr[2] << 0) | 0, 0);
}

int		load_texture(t_cub3d * const cub3d, t_map_init * const map_init, 
	char * const path)
{
	t_list	*idx_node;

	cub3d->textures[map_init->meta_ct].img = mlx_xpm_file_to_image(
		cub3d->mlx,
		path,
		&cub3d->textures[map_init->meta_ct].width,
		&cub3d->textures[map_init->meta_ct].height);
	free(path);
	if (cub3d->textures[map_init->meta_ct].img == NULL)
		return (eerr(ERR_TEX_OPEN));
	cub3d->textures[map_init->meta_ct].addr = (int *)mlx_get_data_addr( \
		cub3d->textures[map_init->meta_ct].img,
		&cub3d->textures[map_init->meta_ct].bits_per_pixel,
		&cub3d->textures[map_init->meta_ct].size_line,
		&cub3d->textures[map_init->meta_ct].endian);
	if (cub3d->textures[map_init->meta_ct].addr == NULL)
		return (eerr(ERR_TEX_OPEN));
	idx_node = ft_lstnew(cub3d->textures[map_init->meta_ct].img);
	if (idx_node == NULL)
		return (1);
	ft_lstadd_back(&cub3d->textures_success, idx_node);
	return (0);
}

int     set_texture(t_cub3d * const cub3d, t_map_init * const map_init)
{
	t_direction direction;
	char        *trim;

	direction = get_direction(map_init->buff);
	if (direction == DEFAULT_DIRECTION)
		return (eerr(ERR_WRONG_DIR));
	if (!ft_isspace(map_init->buff[2]))
		return (eerr(ERR_NO_SPACE_SEPERATOR));
	trim = ft_strtrim(map_init->buff + 2, " \t\v\f\r\n");
	if (!trim)
		return (eerr(ERR_MALLOC));
	if (check_extension(trim, TEX_EXTENSION))
		return (free(trim), eerr(ERR_EXT_XPM));
	ft_printf("map path: %d %s %p\n", map_init->meta_ct - 1, trim, (cub3d->textures)[map_init->meta_ct - 1].img);
	--map_init->meta_ct;
	if (load_texture(cub3d, map_init, trim))
		return (1);
	if (map_init->meta_ct == 0)
	{
		map_init->func = 1;
		map_init->meta_ct = COLOR_COUNT;
	}

	return 0;
}

int     set_color(t_cub3d * const cub3d, struct s_map_init * const map_init)
{
	t_color     color;
	char        *trim;

	color = get_color(map_init->buff);
	if (color == DEFAULT_COLOR)
		return (eerr(ERR_WRONG_COLOR));
	if (!ft_isspace(map_init->buff[1]))
		return (eerr(ERR_NO_SPACE_SEPERATOR));
	trim = ft_strtrim(map_init->buff + 1, " \t\v\f\r\n");
	if (!trim)
		return (eerr(ERR_MALLOC));

	if (set_rgb(trim, &cub3d->floor_ceiling[color]))
		return (free(trim), eerr(ERR_WRONG_COLOR));

	ft_printf("map path: %s\n", trim);
	free(trim);
	ft_printf("%d color: %d, %d, %d, %d\n", color, cub3d->floor_ceiling[color] >> 24,
			(cub3d->floor_ceiling[color] >> 16) & 0x000000ff,
			(cub3d->floor_ceiling[color] >> 8)  & 0x000000ff,
			(cub3d->floor_ceiling[color] >> 0)  & 0x000000ff);
	if (--map_init->meta_ct == 0)
		map_init->cont = 0;
	return 0;
}

int     set_map(t_cub3d * const cub3d, struct s_map_init * const map_init)
{
	(void)map_init;
	int	map_height;
	int	map_width;
	ft_printf("set_map()\n");
	map_height = ft_lstsize(cub3d->map2);
	map_width = 0;
	(void)map_height;
	(void)map_width;
	return (0);
}

// copy struct content
void	init_struct(t_map_init * const dest)
{
	*dest = (t_map_init){
		.func = 0,
		.cont = 1,
		.meta_ct = IMAGE_COUNT,
		.parser = {
			[0] = set_texture,
			[1] = set_color,
			[2] = set_map,
		},
	};
}

int		skip_empty_line(t_map_init * const map_init)
{
	while ("false")
	{
		map_init->buff = get_next_line(map_init->fd);
		if (map_init->buff == NULL)
			return (1);
		map_init->trim = ft_strtrim(map_init->buff, " \t\v\f\r\n");
		if (map_init->trim == NULL)
			return (free(map_init->buff), eerr(ERR_MALLOC));
		if (*map_init->trim != '\0')
			return (0);
		free(map_init->buff);
		map_init->buff = NULL;
		free(map_init->trim);
		map_init->trim = NULL;
	}
	return (1);
}

int		loop_meta_info(t_map_init * const map_init, t_cub3d * const cub3d)
{
	while (map_init->cont)
	{

		if (skip_empty_line(map_init))
			return (eerr(ERR_MISSING));
		free(map_init->buff);
		map_init->buff = map_init->trim;
		ft_printf("trim: |%s|\n", map_init->buff);
		if (map_init->parser[map_init->func](cub3d, map_init))
			return (free(map_init->buff), 1);
		free(map_init->buff);
	}
	return (0);
}

int     is_surroundable_char(unsigned int idx, char *c, void *p)
{
	(void)p;
	(void)idx;
    return (*c == '0' ||
            *c == 'N' ||
            *c == 'S' ||
            *c == 'E' ||
            *c == 'W');
}

int     validate_top_char(unsigned int idx, char *c, void *p)
{
	(void)p;
	(void)idx;
    return (*c != '1' && \
			*c != ' ');
}

int     validate_edge_char(char const * const row)
{
	return (row[0] == '0' || 
			(row[ft_strlen(row) - 1] == '0'));
}

int     validate_row_top(char * const row)
{
	return (ft_strsome(row, validate_top_char, NULL));
}

t_char_type	get_char_type(char const c)
{
	t_char_type	stat;

	if (c == '1')
		stat = FRAME;
	else if (c == ' ')
		stat = SPACE;
	else if (c == '0' ||
			c == 'N' ||
			c == 'S' ||
			c == 'E' ||
			c == 'W')
		stat = SURROUNDABLE;
	else
		stat = INVALID_CHAR;
	return (stat);
}

void	clear_map(t_cub3d * const cub3d)
{
	ft_lstclear(&cub3d->map2, free);
}

// int     validate_mid_char(unsigned int idx, char *c, void *p)
// {
// 	const size_t	prev_len = ft_strlen(p);
// 	t_char_type		curr;
// 	t_char_type		v_prev;
// 	t_char_type		h_next;

// 	if ((*(c + 1) == '\0') || (idx == 0))
// 		return (0);
// 	curr = get_char_type(*c);
// 	h_next = get_char_type(*(c + 1));
// 	if ((prev_len - 1) < idx)
// 		v_prev = INVALID_CHAR;
// 	else
// 		v_prev = get_char_type(((char *)p)[idx]);
// 	if (curr == INVALID_CHAR)
// 		return (1);
// 	{
// 		if (curr == SPACE)
// 			if (h_next == SURROUNDABLE || v_prev == SURROUNDABLE)
// 				return (1);
// 		if (curr == SURROUNDABLE)
// 			if (h_next == SPACE || v_prev == SPACE || v_prev == INVALID_CHAR)
// 				return (1);
// 	}
// 	return(0);
// }

int		check_relative(const size_t prev_len, char const * const row,
	char const * const prev, size_t const i)
{
	t_char_type		curr;
	t_char_type		v_prev;
	t_char_type		h_next;

	curr = get_char_type(row[i]);
	h_next = get_char_type(row[i + 1]);
	if ((prev_len - 1) < i)
		v_prev = INVALID_CHAR;
	else
		v_prev = get_char_type(prev[i]);
	if (curr == INVALID_CHAR)
		return (eerr(ERR_UNVALIDATABLE2));
	{
		if (curr == SPACE)
			if (h_next == SURROUNDABLE || v_prev == SURROUNDABLE)
			{
				ft_printf("%d %d |%c| |%c| %d\n", h_next, v_prev, row[i], prev[i], i);
				return (eerr(ERR_UNVALIDATABLE3));
			}
		if (curr == SURROUNDABLE)
			if (h_next == SPACE || v_prev == SPACE || v_prev == INVALID_CHAR)
				return (eerr(ERR_UNVALIDATABLE4));
	}
	return (0);
}

int		player_detected(t_cub3d * const cub3d, char * const row, size_t i)
{
	if (cub3d->player.posx)
		return (eerr(ERR_MULTIPLAYER));
	cub3d->player.posy = i;
	cub3d->player.posx = ft_lstsize(cub3d->map2) - 0;
	cub3d->player.direction = (int const [UINT8_MAX]){ \
		['N'] = DIR_N, ['E'] = DIR_E, ['S'] = DIR_S, ['W'] = DIR_W} \
		[(int)row[i]];
	cub3d->player.posy += 0.5;
	cub3d->player.posx += 0.5;
	cub3d->player.dirx = sin(deg_to_rad(cub3d->player.direction));
	cub3d->player.diry = cos(deg_to_rad(cub3d->player.direction));
	cub3d->ray.planex = cos(deg_to_rad(cub3d->player.direction)) * FOV;
    cub3d->ray.planey = sin(deg_to_rad(cub3d->player.direction)) * FOV;
	printf("player: x: %lf, y: %lf, direction: %d\n", cub3d->player.posx,
		cub3d->player.posy, cub3d->player.direction);
	row[i] = '0';
	return (0);
}

int		validate_row_mid(char * const row, char * const prev, t_cub3d * const cub3d)
{
	const size_t	prev_len = ft_strlen(prev);
	size_t			i;

	if (validate_edge_char(row))
		return (eerr(ERR_UNVALIDATABLE1));
	i = 0;
	while (row[++i + 1])
	{
		if ((row[i] == 'N' || row[i] == 'S' || row[i] == 'E' || row[i] == 'W'))
			if (player_detected(cub3d, row, i))
				return (1);
		if (check_relative(prev_len, row, prev, i))
			return (1);
	}
	if (prev_len > ++i)
	if (ft_strsome(prev + i, is_surroundable_char, NULL))
		return (eerr(ERR_UNVALIDATABLE5));
    return (0);
}

static int		validate_mid(t_map_init * const map_init, t_cub3d * const cub3d)
{
	while (1)
	{
		ft_lstadd_back(&cub3d->map2, ft_lstnew(map_init->buff));
		map_init->prev = map_init->buff;
		map_init->buff = get_next_line(map_init->fd);
		if (map_init->buff == NULL)
		{
			if (validate_row_top(map_init->prev))
				return (eerr(ERR_UNVALIDATABLE));
			break ;
		}
		map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
		if (map_init->trim == NULL)
			return (free(map_init->buff), eerr(ERR_MALLOC));
		free(map_init->buff);
		map_init->buff = map_init->trim;
		ft_printf("validating row: %s\n", map_init->buff);
		if (validate_row_mid(map_init->buff, map_init->prev, cub3d))
			return (free(map_init->buff), 1);
	}
	return (0);
}

int		loop_map(t_map_init * const map_init, t_cub3d * const cub3d)
{
	if (skip_empty_line(map_init))
		return (eerr(ERR_MISSING));
	free(map_init->trim);
	map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
	if (map_init->trim == NULL)
		return (free(map_init->buff), eerr(ERR_MALLOC));
	free(map_init->buff);
	map_init->buff = map_init->trim;
	ft_printf("validating row: %s\n", map_init->buff);
	if (validate_row_top(map_init->buff))
		return (free(map_init->buff), eerr(ERR_UNVALIDATABLE));
	if (validate_mid(map_init, cub3d))
		return (1);
	if (skip_empty_line(map_init) == 0)
		return (free(map_init->trim), free(map_init->buff), eerr(ERR_2MAP));
	return (0);
}

int    map_init(t_cub3d * const cub3d)
{
	t_map_init map_init;

	ft_printf("initializing map\n");
	init_struct(&map_init);
	if (check_extension(cub3d->map_name, MAP_EXTENSION))
		return (eerr(EXAMPLE_ERR));
	if (open2(cub3d->map_name, O_RDONLY, &map_init.fd))
		return (perror(ERR_PREFIX), eerr(ERR_MAP_OPEN));
	if (loop_meta_info(&map_init, cub3d))
		return (close_err(map_init.fd), 1);
	if (loop_map(&map_init, cub3d))
		return (close_err(map_init.fd), clear_map(cub3d), 1);
	set_map(cub3d, &map_init);
	return (0);
}

void    hook_init(t_cub3d * const cub3d)
{
	mlx_do_key_autorepeatoff(cub3d->mlx);
	// mlx_do_key_autorepeaton(cub3d->mlx);
	ft_printf("[LOG]: init event listeners.\n");
	mlx_hook(cub3d->win_mlx, ON_DESTROY, 0, destroy_game, cub3d);
	mlx_hook(cub3d->win_mlx, 2, (1L<<0), key_press, cub3d);
	mlx_hook(cub3d->win_mlx, 3, (1L<<1), key_release, cub3d);
	// mlx_key_hook(cub3d->win_mlx, key_trigger, cub3d);
	mlx_loop_hook(cub3d->mlx, loop, cub3d);
	// ft_printf("[DEBUG]: end init event listeners.\n");
}

void	pm(t_cub3d * const cub3d)
{
	for (size_t i = 0; i < (size_t)ft_lstsize(cub3d->map2); i++)
		ft_printf("%s\n", ll_nod(cub3d->map2, i)->content);
}

int	screen_buffer_init(t_cub3d * const cub3d, int screen_x, int screen_y)
{
	cub3d->screen_buffer.img = mlx_new_image(cub3d->mlx, screen_x, screen_y);
	if (cub3d->screen_buffer.img == NULL)
		return (1);
	cub3d->screen_buffer.width = screen_x;
	cub3d->screen_buffer.height = screen_y;
	cub3d->screen_buffer.addr = (int *)mlx_get_data_addr(
		cub3d->screen_buffer.img,
		&cub3d->screen_buffer.bits_per_pixel,
		&cub3d->screen_buffer.size_line,
		&cub3d->screen_buffer.endian);
	if (cub3d->screen_buffer.addr == NULL)
		return (1);
	// printf("bits_per_pixel: %d, size_line: %d, endian: %d\n",
	// 	cub3d->screen_buffer.bits_per_pixel,
	// 	cub3d->screen_buffer.size_line,
	// 	cub3d->screen_buffer.endian);
	return (0);
}

int	init_mlx(t_cub3d * const cub3d)
{
	int				screen_x;
	int				screen_y;

	cub3d->mlx = mlx_init();
	if (cub3d->mlx == NULL)
		return (1);
	mlx_get_screen_size(cub3d->mlx, &screen_x, &screen_y);
	screen_x = WIN_WIDTH;
	screen_y = WIN_HEIGHT;
	cub3d->win_mlx = \
		mlx_new_window(cub3d->mlx, screen_x, screen_y, cub3d->map_name);
	if (cub3d->win_mlx == NULL)
		return (1);
	if (screen_buffer_init(cub3d, screen_x, screen_y))
		return (1);
	return (0);
}

int	init_cub3d(t_cub3d * const cub3d)
{
	if (init_mlx(cub3d))
		return (1);
	if (map_init(cub3d))
		return (1);
	ft_printf("SUCCESSFULLY VALIDATED\n");
	pm(cub3d);
	hook_init(cub3d);
	return 0;
}