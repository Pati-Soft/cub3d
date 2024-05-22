#include "cub3d.h"

int     load_images(t_cub3d *cub3d)
{
    (void)cub3d;
    // mlx_xpm_file_to_image()
    return 0;
}

void    map_init(t_cub3d *cub3d)
{
    cub3d->map_height = 12;
    cub3d->map_width = 24;
    cub3d->player.x = 11;
    cub3d->player.y = 9;
    cub3d->player.direction = cub3d->directions['W'];
    load_images(cub3d);
}

void    key_init(t_cub3d *cub3d)
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
int	init_cub3d(t_cub3d *cub3d)
{
    bzero(cub3d, sizeof(t_cub3d)); // safe free
    cub3d->directions['N'] = DIRECTION_N;
	cub3d->directions['E'] = DIRECTION_E;
    cub3d->directions['S'] = DIRECTION_S;
    cub3d->directions['W'] = DIRECTION_W;

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