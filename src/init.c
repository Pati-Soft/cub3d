#include "cub3d.h"

int     load_images(t_cub3d * const cub3d, int index, char *path)
{
	(void)cub3d;
	(void)index;
	(void)path;
	// cub3d->images[index] = mlx_xpm_file_to_image(cub3d->mlx,
	//     );
	return 0;
}

t_direction get_direction(char *buff)
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

t_color get_color(char *buff)
{
	if (!ft_strncmp(TEXT_F, buff, 1))
		return FLOOR;
	if (!ft_strncmp(TEXT_C, buff, 1))
		return CEILING;
	return DEFAULT_COLOR;
}

int check_extension(char const *path, char *ext)
{
	if (ft_strlen(path) < 4 || ft_strncmp(ext,
			path + (ft_strlen(path) - 4), 4))
		return (1);
	return (0);
}

void    close_err(int fd)
{
	if (close(fd) == -1)
		eerr(ERR_CLOSE_FD);
}

// cause `if ((fd = open(path, flags)) == -1)` is forbidden
int open2(char const * const path, int flags, int *fd)
{
	*fd = open(path, flags);
	if (*fd == -1)
		return (1);
	return 0;
}

int     set_rgb(char *buff, unsigned int *color)
{
	char	**split = ft_split(buff, ',');
	int		arr[3];
	
	if (!split)
		return (1);
	if (arrlen(split) != 3)
		return (free_2d(split), 1);
	arr[0] = ft_atoi(split[0]);
	arr[1] = ft_atoi(split[1]);
	arr[2] = ft_atoi(split[2]);
	free_2d(split);
	if (arr[0] > 255 || arr[1] > 255 || arr[2] > 255 || \
		arr[0] < 0 || arr[1] < 0 || arr[2] < 0)
		return (1);
	return (*color = (arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | 0, 0);
}

int     set_texture(t_cub3d * const cub3d, struct s_map_init *map_init)
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
	ft_printf("map path: %s %p\n", trim, ((void **)cub3d->img)[map_init->meta_ct - 1]);
	ft_printf("a %d %p, %p\n", map_init->meta_ct, cub3d->mlx, cub3d->mlx);
	((void **)cub3d->img)[--map_init->meta_ct] = mlx_xpm_file_to_image(cub3d->mlx,
		trim, (int *)&cub3d->texture_w, (int *)&cub3d->texture_h);
	free(trim);
	if (cub3d->img[map_init->meta_ct] == NULL)
		return (eerr(ERR_TEX_OPEN));
	if (map_init->meta_ct == 0)
	{
		map_init->func = 1;
		map_init->meta_ct = COLOR_COUNT;
	}
	return 0;
}

int     set_color(t_cub3d * const cub3d, struct s_map_init *map_init)
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

int     set_map(t_cub3d * const cub3d, struct s_map_init *map_init)
{
	ft_printf("set_map()\n");
	*(int *)&cub3d->map_height = ft_lstsize(cub3d->map2);
	*(int *)&cub3d->map_width = 0;
	cub3d->player.x = 12;
	cub3d->player.y = 4;
	cub3d->player.direction = cub3d->directions['W'];

	return (0);
}


void	init_struct(t_map_init *dest)
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

int		skip_empty_line(t_map_init *map_init)
{
	while ("false")
	{
		map_init->buff = get_next_line(map_init->fd);
		if (map_init->buff == NULL)
			return (1);
		map_init->trim = ft_strtrim(map_init->buff, " \t\v\f\r\n");
		if (map_init->trim == NULL)
			return (eerr(ERR_MALLOC));
		if (*map_init->trim != '\0')
			return (0);
		free(map_init->buff);
		map_init->buff = NULL;
		free(map_init->trim);
		map_init->trim = NULL;
	}
	return (1);
}

int		loop_meta_info(t_map_init *map_init, t_cub3d *cub3d)
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

int     validate_edge_char(char *row)
{
	return (row[0] == '0' || 
			(row[ft_strlen(row) - 1] == '0'));
}

int     validate_row_top(char *row)
{
	return (ft_strsome(row, validate_top_char, NULL));
}

t_char_type	get_char_type(char c)
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

int     validate_mid_char(unsigned int idx, char *c, void *p)
{
	const size_t	prev_len = ft_strlen(p);
	t_char_type		curr;
	t_char_type		v_prev;
	t_char_type		h_next;

	if ((*(c + 1) == '\0') || (idx == 0))
		return (0);
	curr = get_char_type(*c);
	h_next = get_char_type(*(c + 1));
	if ((prev_len - 1) < idx)
		v_prev = INVALID_CHAR;
	else
		v_prev = get_char_type(((char *)p)[idx]);
	if (curr == INVALID_CHAR)
		return (1);
	{
		if (curr == SPACE)
			if (h_next == SURROUNDABLE || v_prev == SURROUNDABLE)
				return (1);
		if (curr == SURROUNDABLE)
			if (h_next == SPACE || v_prev == SPACE || v_prev == INVALID_CHAR)
				return (1);
	}
	return(0);
}

int		validate_row_mid(char *row, char *prev)
{
	const size_t	prev_len = ft_strlen(prev);
	unsigned int	i;
	t_char_type		curr;
	t_char_type		v_prev;
	t_char_type		h_next;

	if (validate_edge_char(row))
		return (1, eerr("RETURN 1\n"));
	i = 0;
	while (row[i])
	{
		if ((row[i + 1] == '\0') || (i == 0))
		{
			i++;
			continue ;
		}
		curr = get_char_type(row[i]);
		h_next = get_char_type(row[i + 1]);
		if ((prev_len - 1) < i)
			v_prev = INVALID_CHAR;
		else
			v_prev = get_char_type(prev[i]);
		if (curr == INVALID_CHAR)
			return (1, eerr("RETURN 2\n"));
		{
			if (curr == SPACE)
				if (h_next == SURROUNDABLE || v_prev == SURROUNDABLE)
				{
					ft_printf("%d %d |%c| |%c| %d\n", h_next, v_prev, row[i], prev[i], i);
					return (1, eerr("RETURN 3\n"));
				}
			if (curr == SURROUNDABLE)
				if (h_next == SPACE || v_prev == SPACE || v_prev == INVALID_CHAR)
					return (1, eerr("RETURN 4\n"));
		}
		i++;
	}
	if (prev_len > i)
	if (ft_strsome(prev + i, is_surroundable_char, NULL))
		return (1, eerr("RETURN 5\n"));
    return (0);
}

int     validate_row_bot()
{
	return (0);
}

int		loop_map(t_map_init *map_init, t_cub3d *cub3d)
{
	char *prev;

	prev = NULL;
	ft_printf("HERE HERE HERE HERE HERE HERE HERE HERE \n");
	if (skip_empty_line(map_init))
		return (free(map_init->trim), free(map_init->buff), eerr(ERR_MISSING));
	free(map_init->trim);

	map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
	if (map_init->trim == NULL)
		return (free(map_init->buff), eerr(ERR_MALLOC));
	free(map_init->buff);
	map_init->buff = map_init->trim;
	ft_printf("validating row: %s\n", map_init->buff);
	if (validate_row_top(map_init->buff))
		return (free(map_init->buff), 1);
	while (1)
	{
		ft_lstadd_back(&cub3d->map2, ft_lstnew(map_init->buff));
		// free(prev);
		prev = map_init->buff;

		map_init->buff = get_next_line(map_init->fd);
		if (map_init->buff == NULL)
		{
			if (validate_row_top(prev))
				return (free(prev), eerr(ERR_UNVALIDATABLE));
			// free(prev);
			break ;
			// ~ end
		}

		map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
		if (map_init->trim == NULL)
			return (free(map_init->buff), free(prev), eerr(ERR_MALLOC));
		free(map_init->buff);
		map_init->buff = map_init->trim;
		ft_printf("validating row: %s\n", map_init->buff);
		if (validate_row_mid(map_init->buff, prev))
			return (free(map_init->buff), free(prev), eerr(ERR_UNVALIDATABLE));
	}

	if (skip_empty_line(map_init) == 0)
		return (free(map_init->trim), eerr(ERR_2MAP));

	// if (skip_empty_line(map_init))
	// 	return (eerr(ERR_MISSING));
	// free(map_init->trim);
	// map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
	// if (map_init->trim == NULL)
	// 	return (free(map_init->buff), eerr(ERR_MALLOC));
	// free(map_init->buff);
	// map_init->buff = map_init->trim;
	// ft_printf("validating row: %s\n", map_init->buff);
	// if (validate_row_top(map_init->buff))
	// 	return (free(map_init->buff), 1);
	// ft_lstadd_back(&cub3d->map2, ft_lstnew(map_init->buff));
	// prev = map_init->buff;
	// map_init->buff = get_next_line(map_init->fd);
	// if (!map_init->buff)
	// 	return (free(prev), 1);
	// map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
	// if (map_init->trim == NULL)
	// 	return (free(map_init->buff), free(prev), eerr(ERR_MALLOC));
	// free(map_init->buff);
	// map_init->buff = map_init->trim;
	// while (map_init->buff)
	// {
	// 	ft_printf("validating row: %s\n", map_init->buff);
	// 	if (validate_row_mid(map_init->buff, prev))
	// 		return (free(prev), free(map_init->buff), 1);
	// 	// free(prev);
	// 	ft_lstadd_back(&cub3d->map2, ft_lstnew(map_init->buff));
	// 	prev = map_init->buff;
	// 	map_init->buff = get_next_line(map_init->fd);

	// 	if (!map_init->buff)
	// 		break ;
	// 	map_init->trim = ft_strrtrim(map_init->buff, " \t\v\f\r\n");
	// 	if (map_init->trim == NULL)
	// 		return (free(map_init->buff), free(prev), eerr(ERR_MALLOC));
	// 	free(map_init->buff);
	// 	map_init->buff = map_init->trim;
	// 	// yanlar 1 olmali, en ust ve alt 1 olmali 
	// 	// bos satir olmamali

	// 	// if (*map_init->buff == '\0')
	// 	// {
	// 	// 	free(map_init->buff);
	// 	// 	continue;
	// 	// }
	// 	// if (map_init->parser[map_init->func](cub3d, map_init))
	// 	// 	return (free(map_init->buff), 1);
	// }
	ft_printf("SUCCESSFULLY VALIDATED\n");
	for (size_t i = 0; i < ft_lstsize(cub3d->map2); i++)
		ft_printf("%s\n", ll_nod(cub3d->map2, i)->content);
	free(prev);
	return (0);
}

int    map_init(t_cub3d * const cub3d)
{
	t_map_init map_init;

	init_struct(&map_init);
	if (check_extension(cub3d->map_name, MAP_EXTENSION))
		return (eerr(EXAMPLE_ERR));
	if (open2(cub3d->map_name, O_RDONLY, &map_init.fd))
		return (perror(ERR_PREFIX), eerr(ERR_MAP_OPEN));
	if (loop_meta_info(&map_init, cub3d))
		return (close_err(map_init.fd), 1);
	if (loop_map(&map_init, cub3d))
		return (close_err(map_init.fd), 1);
	set_map(cub3d, &map_init);
	return (0);
}

void    key_init(t_cub3d * const cub3d)
{
	mlx_hook(cub3d->win_mlx, ON_DESTROY, 0, destroy_window, cub3d);
	mlx_hook(cub3d->win_mlx, 2, 0, key_trigger, cub3d);
	// mlx_key_hook(cub3d->win_mlx, key_trigger, cub3d);

}

/**
 * @brief 
 * 
 * @param cub3d 
 * @return int 
 */
int	init_cub3d(t_cub3d * const cub3d)
{
	// bzero(cub3d, sizeof(t_cub3d)); // safe free
	*(int *)&cub3d->directions['N'] = DIRECTION_N;
	*(int *)&cub3d->directions['E'] = DIRECTION_E;
	*(int *)&cub3d->directions['S'] = DIRECTION_S;
	*(int *)&cub3d->directions['W'] = DIRECTION_W;

	cub3d->mlx = mlx_init();
	if (map_init(cub3d))
		return 1;
	cub3d->win_mlx = mlx_new_window(cub3d->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!cub3d->mlx || !cub3d->win_mlx)
		return 1;
	key_init(cub3d);
	mlx_loop(cub3d->mlx);
	//mlx destroy event
	return 0;
}