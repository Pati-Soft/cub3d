#include "cub3d.h"

int key_trigger(int keycode, t_cub3d *cub3d)
{
    ft_printf("%d\n", keycode);
    if (keycode == MLX_KEY_ESC || keycode == MLX_KEY_Q)
        destroy_window(cub3d);
    if (keycode == MLX_KEY_W)
        ft_printf("W\n");
    return 0;
}