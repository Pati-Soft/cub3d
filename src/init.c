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

int    map_init(t_cub3d * const cub3d)
{
    int const   fd = open(cub3d->map_name, O_RDONLY);
    char        *buff;
    int         meta_ct;
    int         line_i;

    line_i = 0;
    meta_ct = IMAGE_COUNT;
    if (ft_strlen(cub3d->map_name) < 4 || ft_strncmp(EXTENSION,
            cub3d->map_name + (ft_strlen(cub3d->map_name) - 4), 4))
        return (err(ERR_PREFIX), err(EXAMPLE_ERR));
    if (fd < -1)
        return (err(ERR_PREFIX), err(ERR_MAP_OPEN));
    while (meta_ct--)
    {
        buff = get_next_line(fd);
        if (!buff)
            return (err(ERR_PREFIX), err(ERR_MAP_CORRUPTED));
        // buff[ft_strlen(buff) - 1] = '\0';
        if (ft_strncmp(TEXT_NO, buff, 2) && ft_strncmp(TEXT_SO, buff, 2) &&
            ft_strncmp(TEXT_WE, buff, 2) && ft_strncmp(TEXT_EA, buff, 2))
            return (err(ERR_PREFIX), err(ERR_MAP_CORRUPTED));
        line_i += 2;
        if (!ft_isspace(buff[line_i++]))
            return (err(ERR_PREFIX), err(ERR_MAP_CORRUPTED));
        ((void **)cub3d->img)[meta_ct - 1] = mlx_xpm_file_to_image(cub3d->mlx,
            buff + line_i, (int *)&cub3d->texture_w, (int *)&cub3d->texture_h);
        if (cub3d->img[meta_ct - 1] == NULL)
            return (err(ERR_PREFIX), err(ERR_TEX_OPEN));
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

    map_init(cub3d);
    cub3d->mlx = mlx_init();
    cub3d->win_mlx = mlx_new_window(cub3d->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    if (!cub3d->mlx || !cub3d->win_mlx)
        return 1;
    key_init(cub3d);
    mlx_loop(cub3d->mlx);
    //mlx destroy event
    return 0;
}