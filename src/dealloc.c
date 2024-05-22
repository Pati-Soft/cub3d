#include "cub3d.h"

void    dealloc_cub3d(t_cub3d *cub3d)
{
    free(cub3d->mlx);
    free(cub3d->win_mlx);
    // free(cub3d->map);
}

int    destroy_window(t_cub3d *cub3d)
{
    
    printf("Window destroyed: %d\n", (mlx_destroy_window(cub3d->mlx, cub3d->win_mlx)));
    cub3d->win_mlx = NULL;
    cub3d->mlx = NULL;
    dealloc_cub3d(cub3d);
    exit(0);
    return (0);
}