#include "cub3d.h"

int key_trigger(int keycode, t_cub3d *cub3d)
{
    ft_printf("%d\n", keycode);
    if (keycode == X_KEY_ESC)
        destroy_window(cub3d);
    return 0;
}