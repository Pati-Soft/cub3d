#include "cub3d.h"

int	is_character(char c)
{
	if (c == NORTH_CHAR || c == SOUTH_CHAR
		|| c == EAST_CHAR || c == WEST_CHAR)
		return (1);
	return (0);
}

void	key_w(t_cub3d *cub3d)
{
    // printf("key_w: x:%d, y:%d => |%c| => %d:|%s|\n",
    //     (int)(cub3d->ray.posx + cub3d->ray.dirx * MOVEMENT_SPEED),
    //     (int)(cub3d->ray.posy),
    //     ((char *)ll_nod(cub3d->map2,
    //         (int)(cub3d->ray.posx + cub3d->ray.dirx * MOVEMENT_SPEED)))
    //         [(int)(cub3d->ray.posy)],
    //     (int)(cub3d->ray.posx + cub3d->ray.dirx * MOVEMENT_SPEED),
    //     ((char *)ll_nod(cub3d->map2,
    //         (int)(cub3d->ray.posx + cub3d->ray.dirx * MOVEMENT_SPEED)))
    //     );
    // ((char *)ll_nod(cub3d->map2, ))
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx + cub3d->ray.dirx
			* MOVEMENT_SPEED))->content)[(int)(cub3d->ray.posy)] == '0'
		|| is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx + cub3d->ray.dirx
				* MOVEMENT_SPEED))->content)[(int)(cub3d->ray.posy)]))
    {
		cub3d->ray.posx += cub3d->ray.dirx * MOVEMENT_SPEED;
    }

	if (((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx)->content)[(int)(cub3d->ray.posy
		+ cub3d->ray.diry * MOVEMENT_SPEED)] == '0'
		|| is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx)->content)
		[(int)(cub3d->ray.posy + cub3d->ray.diry * MOVEMENT_SPEED)]))
    {
		cub3d->ray.posy += cub3d->ray.diry * MOVEMENT_SPEED;
    }
}

// void	key_s(t_cub3d *cub3d)
// {
// 	if (data->map->map[(int)(cub3d->ray.posx - cub3d->ray.dirx
// 			* MOVEMENT_SPEED)][(int)(cub3d->ray.posy)] == '0'
// 		|| is_character(data->map->map[(int)(cub3d->ray.posx - cub3d->ray.dirx
// 				* MOVEMENT_SPEED)][(int)(cub3d->ray.posy)]))
// 		cub3d->ray.posx -= cub3d->ray.dirx * MOVEMENT_SPEED;
// 	if (data->map->map[(int)(cub3d->ray.posx)][(int)(cub3d->ray.posy
// 			- cub3d->ray.diry * MOVEMENT_SPEED)] == '0'
// 		|| is_character(data->map->map[(int)(cub3d->ray.posx)][
// 			(int)(cub3d->ray.posy - cub3d->ray.diry * MOVEMENT_SPEED)]))
// 		cub3d->ray.posy -= cub3d->ray.diry * MOVEMENT_SPEED;
// }

void    key_s(t_cub3d *cub3d)
{
    if (((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx - cub3d->ray.dirx
            * MOVEMENT_SPEED))->content)[(int)(cub3d->ray.posy)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx - cub3d->ray.dirx
                * MOVEMENT_SPEED)))[(int)(cub3d->ray.posy)]))
        cub3d->ray.posx -= cub3d->ray.dirx * MOVEMENT_SPEED;
    if (((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx)->content)[(int)(cub3d->ray.posy
        - cub3d->ray.diry * MOVEMENT_SPEED)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx))
        [(int)(cub3d->ray.posy - cub3d->ray.diry * MOVEMENT_SPEED)]))
        cub3d->ray.posy -= cub3d->ray.diry * MOVEMENT_SPEED;
}

// void	key_d(t_cub3d *cub3d)
// {
// 	if (data->map->map[(int)(cub3d->ray.posx + cub3d->ray.diry
// 			* MOVEMENT_SPEED)][(int)(cub3d->ray.posy)] == '0'
// 		|| is_character(data->map->map[(int)(cub3d->ray.posx + cub3d->ray.diry
// 				* MOVEMENT_SPEED)][(int)(cub3d->ray.posy)]))
// 		cub3d->ray.posx += cub3d->ray.diry * MOVEMENT_SPEED;
// 	if (data->map->map[(int)(cub3d->ray.posx)][(int)(cub3d->ray.posy
// 			- cub3d->ray.dirx * MOVEMENT_SPEED)] == '0'
// 		|| is_character(data->map->map[(int)(cub3d->ray.posx)]
// 		[(int)(cub3d->ray.posy - cub3d->ray.dirx * MOVEMENT_SPEED)]))
// 		cub3d->ray.posy -= cub3d->ray.dirx * MOVEMENT_SPEED;
// }

void    key_d(t_cub3d *cub3d)
{
    if (((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx + cub3d->ray.diry
            * MOVEMENT_SPEED))->content)[(int)(cub3d->ray.posy)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx + cub3d->ray.diry
                * MOVEMENT_SPEED)))[(int)(cub3d->ray.posy)]))
        cub3d->ray.posx += cub3d->ray.diry * MOVEMENT_SPEED;
    if (((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx)->content)[(int)(cub3d->ray.posy
        - cub3d->ray.dirx * MOVEMENT_SPEED)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx))
        [(int)(cub3d->ray.posy - cub3d->ray.dirx * MOVEMENT_SPEED)]))
        cub3d->ray.posy -= cub3d->ray.dirx * MOVEMENT_SPEED;
}

// void	key_a(t_cub3d *cub3d)
// {
// 	if (data->map->map[(int)(cub3d->ray.posx - cub3d->ray.diry
// 			* MOVEMENT_SPEED)][(int)(cub3d->ray.posy)] == '0'
// 		|| is_character(data->map->map[(int)(cub3d->ray.posx - cub3d->ray.diry
// 				* MOVEMENT_SPEED)][(int)(cub3d->ray.posy)]))
// 		cub3d->ray.posx -= cub3d->ray.diry * MOVEMENT_SPEED;
// 	if (data->map->map[(int)(cub3d->ray.posx)][(int)(cub3d->ray.posy
// 			+ cub3d->ray.dirx * MOVEMENT_SPEED)] == '0'
// 		|| is_character(data->map->map[(int)(cub3d->ray.posx)]
// 		[(int)(cub3d->ray.posy + cub3d->ray.dirx * MOVEMENT_SPEED)]))
// 		cub3d->ray.posy += cub3d->ray.dirx * MOVEMENT_SPEED;
// }

void    key_a(t_cub3d *cub3d)
{
    if (((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx - cub3d->ray.diry
            * MOVEMENT_SPEED))->content)[(int)(cub3d->ray.posy)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->ray.posx - cub3d->ray.diry
                * MOVEMENT_SPEED)))[(int)(cub3d->ray.posy)]))
        cub3d->ray.posx -= cub3d->ray.diry * MOVEMENT_SPEED;
    if (((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx)->content)[(int)(cub3d->ray.posy
        + cub3d->ray.dirx * MOVEMENT_SPEED)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->ray.posx))
        [(int)(cub3d->ray.posy + cub3d->ray.dirx * MOVEMENT_SPEED)]))
        cub3d->ray.posy += cub3d->ray.dirx * MOVEMENT_SPEED;
}



void	key_right(t_cub3d *cub3d)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub3d->ray.dirx;
	cub3d->ray.dirx = cub3d->ray.dirx * cos(-ROTATION_SPEED) - cub3d->ray.diry
		* sin(-ROTATION_SPEED);
	cub3d->ray.diry = old_dirx * sin(-ROTATION_SPEED) + cub3d->ray.diry
		* cos(-ROTATION_SPEED);
	old_planex = cub3d->ray.planex;
	cub3d->ray.planex = cub3d->ray.planex * cos(-ROTATION_SPEED) - cub3d->ray.planey
		* sin(-ROTATION_SPEED);
	cub3d->ray.planey = old_planex * sin(-ROTATION_SPEED) + cub3d->ray.planey
		* cos(-ROTATION_SPEED);
}

void    key_left(t_cub3d *cub3d)
{
    double	old_dirx;
    double	old_planex;

    old_dirx = cub3d->ray.dirx;
    cub3d->ray.dirx = cub3d->ray.dirx * cos(ROTATION_SPEED) - cub3d->ray.diry
        * sin(ROTATION_SPEED);
    cub3d->ray.diry = old_dirx * sin(ROTATION_SPEED) + cub3d->ray.diry
        * cos(ROTATION_SPEED);
    old_planex = cub3d->ray.planex;
    cub3d->ray.planex = cub3d->ray.planex * cos(ROTATION_SPEED) - cub3d->ray.planey
        * sin(ROTATION_SPEED);
    cub3d->ray.planey = old_planex * sin(ROTATION_SPEED) + cub3d->ray.planey
        * cos(ROTATION_SPEED);
}

void	ft_move(t_cub3d *cub3d)
{
	if (cub3d->player.keys[KEY_W_IDX])
		key_w(cub3d);
	if (cub3d->player.keys[KEY_A_IDX])
		key_a(cub3d);
	if (cub3d->player.keys[KEY_S_IDX])
		key_s(cub3d);
	if (cub3d->player.keys[KEY_D_IDX])
		key_d(cub3d);
	if (cub3d->player.keys[KEY_LARROW_IDX])
		key_left(cub3d);
	if (cub3d->player.keys[KEY_RARROW_IDX])
		key_right(cub3d);
}

int	ft_player_move(t_cub3d *cub3d)
{
	ft_move(cub3d);
	// mouse_hook(cub3d);
	return (0);
}

int key_release(int keycode, t_cub3d *cub3d)
{
    (void)cub3d;
    (void)keycode;
    ft_printf("release %d\n", keycode);
    if (keycode == MLX_KEY_W)
        cub3d->player.keys[KEY_W_IDX] = 0;
    if (keycode == MLX_KEY_A)
        cub3d->player.keys[KEY_A_IDX] = 0;
    if (keycode == MLX_KEY_S)
        cub3d->player.keys[KEY_S_IDX] = 0;
    if (keycode == MLX_KEY_D)
        cub3d->player.keys[KEY_D_IDX] = 0;

    if (keycode == MLX_KEY_LARROW)
        cub3d->player.keys[KEY_LARROW_IDX] = 0;
    if (keycode == MLX_KEY_RARROW)
        cub3d->player.keys[KEY_RARROW_IDX] = 0;

    return 0;
}

int key_press(int keycode, t_cub3d *cub3d)
{
    ft_printf("press %d\n", keycode);
    if (keycode == MLX_KEY_ESC || keycode == MLX_KEY_Q)
        destroy_window(cub3d);
    
    if (keycode == MLX_KEY_W)
        cub3d->player.keys[KEY_W_IDX] = 1;
    if (keycode == MLX_KEY_A)
        cub3d->player.keys[KEY_A_IDX] = 1;
    if (keycode == MLX_KEY_S)
        cub3d->player.keys[KEY_S_IDX] = 1;
    if (keycode == MLX_KEY_D)
        cub3d->player.keys[KEY_D_IDX] = 1;

    if (keycode == MLX_KEY_LARROW)
        cub3d->player.keys[KEY_LARROW_IDX] = 1;
    if (keycode == MLX_KEY_RARROW)
        cub3d->player.keys[KEY_RARROW_IDX] = 1;
    return 0;
}