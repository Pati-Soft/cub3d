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

int     set_rgb(char *buff, int *color)
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
	//◦ Except for the map, each type of information from an element can be separated
	// by one or more space(s).

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
		map_init->func = 3;
	return 0;
}

int     set_map(t_cub3d * const cub3d, struct s_map_init *map_init)
{
	ft_printf("set_map()");
	*(int *)&cub3d->map_height = 12;
	*(int *)&cub3d->map_width = 24;
	cub3d->player.x = 11;
	cub3d->player.y = 9;
	cub3d->player.direction = cub3d->directions['W'];

	return (0);
}

int		cont_end(t_cub3d * const cub3d, struct s_map_init *map_init)
{
	map_init->cont = 0;
	return (0);
}

int    map_init(t_cub3d * const cub3d)
{
	t_map_init * const map_init = &(t_map_init){
		.func = 0,
		.cont = 1,
		.meta_ct = IMAGE_COUNT,
		.parser = {
			[0] = set_texture,
			[1] = set_color,
			[2] = set_map,
			[3] = cont_end,
		},
	};

	if (check_extension(cub3d->map_name, MAP_EXTENSION))
		return (eerr(EXAMPLE_ERR));
	if (open2(cub3d->map_name, O_RDONLY, &map_init->fd))
		return (perror(ERR_PREFIX), eerr(ERR_MAP_OPEN));
	while (map_init->cont)
	{
		map_init->buff = get_next_line(map_init->fd);
		if (!map_init->buff && map_init->cont)
			return (close_err(map_init->fd), eerr(ERR_MISSING));
		map_init->trim = ft_strtrim(map_init->buff, " \t\v\f\r\n");
		if (!map_init->trim)
			return (free(map_init->buff), close_err(map_init->fd), eerr(ERR_MAP_CORRUPTED));
		free(map_init->buff);
		map_init->buff = map_init->trim;
		ft_printf("trim: |%s|\n", map_init->buff);
		if (*map_init->buff == '\0')
		{
			free(map_init->buff);
			continue;
		}
		if (map_init->parser[map_init->func](cub3d, map_init))
			return (free(map_init->buff), close_err(map_init->fd), 1);
		free(map_init->buff);
	}
	set_map(cub3d, map_init);
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