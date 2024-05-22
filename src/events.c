#include "cub3d.h"

int key_trigger(int keycode, t_cub3d *cub3d)
{
    if (keycode == 53)
        destroy_window(cub3d);
    return 0;
}