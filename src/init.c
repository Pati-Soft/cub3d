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
    return DEFAULT;
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
int open2(char *path, int flags, int *fd)
{
    *fd = open(path, flags);
    if (*fd == -1)
        return (1);
    return 0;
}

int    map_init(t_cub3d * const cub3d)
{
    int         fd;
    char        *buff;
    int         meta_ct;
    int         line_i;
    t_direction direction;

    line_i = 0;
    meta_ct = IMAGE_COUNT;
    if (check_extension(cub3d->map_name, MAP_EXTENSION))
        return (eerr(EXAMPLE_ERR));
    if (open2(cub3d->map_name, O_RDONLY, &fd))
        return (perror(ERR_PREFIX), eerr(ERR_MAP_OPEN));
    while (meta_ct--)
    {
        buff = get_next_line(fd);
        if (!buff)
            return (close_err(fd), eerr(ERR_MISSING));
        buff[ft_strlen(buff) - 1] = '\0';
        direction = get_direction(buff);
        if (direction == DEFAULT)
            return (free(buff), close_err(fd), eerr(ERR_WRONG_DIR));
        line_i += 2;
        if (!ft_isspace(buff[line_i++]))
            return (free(buff), close_err(fd), eerr(ERR_NO_SPACE_SEPERATOR));
        ft_printf("buff: %s\n", buff + line_i);
        if (check_extension(buff + line_i, TEX_EXTENSION))
            return (free(buff), close_err(fd), eerr(ERR_EXT_XPM));
        ((void **)cub3d->img)[meta_ct - 1] = mlx_xpm_file_to_image(cub3d->mlx,
            buff + line_i, (int *)&cub3d->texture_w, (int *)&cub3d->texture_h);
        if (cub3d->img[meta_ct - 1] == NULL)
            return (eerr(ERR_TEX_OPEN));
        free(buff);
    }
    
    buff[ft_strlen(buff) - 1] = '\0';

        
    *(int *)&cub3d->map_height = 12;
    *(int *)&cub3d->map_width = 24;
    cub3d->player.x = 11;
    cub3d->player.y = 9;
    cub3d->player.direction = cub3d->directions['W'];
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

    if (map_init(cub3d))
        return 1;
    cub3d->mlx = mlx_init();
    cub3d->win_mlx = mlx_new_window(cub3d->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    if (!cub3d->mlx || !cub3d->win_mlx)
        return 1;
    key_init(cub3d);
    mlx_loop(cub3d->mlx);
    //mlx destroy event
    return 0;
}