#include "cub3d.h"

int	is_character(char const c)
{
	if (c == NORTH_CHAR || c == SOUTH_CHAR
		|| c == EAST_CHAR || c == WEST_CHAR)
		return (1);
	return (0);
}

void	key_w(t_cub3d * const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.dirx
			* MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0'
		|| is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.dirx
				* MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)]))
    {
		cub3d->player.posx += cub3d->player.dirx * MOVEMENT_SPEED;
    }

	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(cub3d->player.posy
		+ cub3d->player.diry * MOVEMENT_SPEED)] == '0'
		|| is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)
		[(int)(cub3d->player.posy + cub3d->player.diry * MOVEMENT_SPEED)]))
    {
		cub3d->player.posy += cub3d->player.diry * MOVEMENT_SPEED;
    }
}

void    key_s(t_cub3d * const cub3d)
{
    if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.dirx
            * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.dirx
                * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
        cub3d->player.posx -= cub3d->player.dirx * MOVEMENT_SPEED;
    if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(cub3d->player.posy
        - cub3d->player.diry * MOVEMENT_SPEED)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))
        [(int)(cub3d->player.posy - cub3d->player.diry * MOVEMENT_SPEED)]))
        cub3d->player.posy -= cub3d->player.diry * MOVEMENT_SPEED;
}

void    key_d(t_cub3d * const cub3d)
{
    if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.diry
            * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.diry
                * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
        cub3d->player.posx += cub3d->player.diry * MOVEMENT_SPEED;
    if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(cub3d->player.posy
        - cub3d->player.dirx * MOVEMENT_SPEED)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))
        [(int)(cub3d->player.posy - cub3d->player.dirx * MOVEMENT_SPEED)]))
        cub3d->player.posy -= cub3d->player.dirx * MOVEMENT_SPEED;
}

void    key_a(t_cub3d * const cub3d)
{
    if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.diry
            * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.diry
                * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
        cub3d->player.posx -= cub3d->player.diry * MOVEMENT_SPEED;
    if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(cub3d->player.posy
        + cub3d->player.dirx * MOVEMENT_SPEED)] == '0'
        || is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))
        [(int)(cub3d->player.posy + cub3d->player.dirx * MOVEMENT_SPEED)]))
        cub3d->player.posy += cub3d->player.dirx * MOVEMENT_SPEED;
}

void	key_right(t_cub3d * const cub3d)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub3d->player.dirx;
	cub3d->player.dirx = cub3d->player.dirx * cos(-ROTATION_SPEED) - cub3d->player.diry
		* sin(-ROTATION_SPEED);
	cub3d->player.diry = old_dirx * sin(-ROTATION_SPEED) + cub3d->player.diry
		* cos(-ROTATION_SPEED);
	old_planex = cub3d->ray.planex;
	cub3d->ray.planex = cub3d->ray.planex * cos(-ROTATION_SPEED) - cub3d->ray.planey
		* sin(-ROTATION_SPEED);
	cub3d->ray.planey = old_planex * sin(-ROTATION_SPEED) + cub3d->ray.planey
		* cos(-ROTATION_SPEED);
}

void    key_left(t_cub3d * const cub3d)
{
    double	old_dirx;
    double	old_planex;

    old_dirx = cub3d->player.dirx;
    cub3d->player.dirx = cub3d->player.dirx * cos(ROTATION_SPEED) - cub3d->player.diry
        * sin(ROTATION_SPEED);
    cub3d->player.diry = old_dirx * sin(ROTATION_SPEED) + cub3d->player.diry
        * cos(ROTATION_SPEED);
    old_planex = cub3d->ray.planex;
    cub3d->ray.planex = cub3d->ray.planex * cos(ROTATION_SPEED) - cub3d->ray.planey
        * sin(ROTATION_SPEED);
    cub3d->ray.planey = old_planex * sin(ROTATION_SPEED) + cub3d->ray.planey
        * cos(ROTATION_SPEED);
}

void	ft_move(t_cub3d * const cub3d)
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

int	ft_player_move(t_cub3d * const cub3d)
{
	ft_move(cub3d);
	// mouse_hook(cub3d);
	return (0);
}

int key_release(int const keycode, t_cub3d * const cub3d)
{
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

int key_press(int const keycode, t_cub3d * const cub3d)
{
    ft_printf("press %d\n", keycode);
    if (keycode == MLX_KEY_ESC || keycode == MLX_KEY_Q)
        destroy_game(cub3d);
    
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

// void a(){
//     while (x < cub3d->screen_buffer.width)
// 	{
// 		cub3d->ray.camerax = (2 * x) / (double)cub3d->screen_buffer.width - 1;
// 		cub3d->ray.raydirx = cub3d->player.dirx + (cub3d->ray.planex
// 			* cub3d->ray.camerax);
// 		cub3d->ray.raydiry = cub3d->player.diry + (cub3d->ray.planey
// 			* cub3d->ray.camerax);
// 		cub3d->ray.map_y = (int)cub3d->player.posx;
// 		cub3d->ray.map_x = (int)cub3d->player.posy;
// 		cub3d->ray.deltadistx = fabs(1 / cub3d->ray.raydirx);
// 		cub3d->ray.deltadisty = fabs(1 / cub3d->ray.raydiry);

//         if (cub3d->ray.raydirx < 0)
//         {
//             cub3d->ray.stepx = -1;
//             cub3d->ray.sidedistx = (cub3d->player.posx - cub3d->ray.map_y)
//                 * cub3d->ray.deltadistx;
//         }
//         else
//         {
//             cub3d->ray.stepx = 1;
//             cub3d->ray.sidedistx = (cub3d->ray.map_y + 1.0 - cub3d->player.posx)
//                 * cub3d->ray.deltadistx;
//         }
//         if (cub3d->ray.raydiry < 0)
//         {
//             cub3d->ray.stepy = -1;
//             cub3d->ray.sidedisty = (cub3d->player.posy - cub3d->ray.map_x)
//                 * cub3d->ray.deltadisty;
//         }
//         else
//         {
//             cub3d->ray.stepy = 1;
//             cub3d->ray.sidedisty = (cub3d->ray.map_x + 1.0 - cub3d->player.posy)
//                 * cub3d->ray.deltadisty;
//         }
        
//         cub3d->ray.wall = 0;
//         while (!cub3d->ray.wall)
//         {
//             if (cub3d->ray.sidedistx < cub3d->ray.sidedisty)
//             {
//             // printf("1\n");
//                 cub3d->ray.sidedistx += cub3d->ray.deltadistx;
//                 cub3d->ray.map_y += cub3d->ray.stepx;
//                 cub3d->ray.side = 0;
//             }
//             else
//             {
//             // printf("2\n");
//                 cub3d->ray.sidedisty += cub3d->ray.deltadisty;
//                 cub3d->ray.map_x += cub3d->ray.stepy;
//                 cub3d->ray.side = 1;
//             }
//             // printf("3\n");
//             // printf("cub3d->ray.map_y: %d, cub3d->ray.map_x: %d\n", cub3d->ray.map_y, cub3d->ray.map_x);
//             // ((char *)ll_nod(cub3d->map2, cub3d->ray.map_y)->content)[cub3d->ray.map_x] = 'X';
//             // pm(cub3d);
//             // printf("map2\n");
//             if (((char *)ll_nod(cub3d->map2, cub3d->ray.map_y)->content) \
//                 [cub3d->ray.map_x] == WALL_CHAR)
//             {
//                 cub3d->ray.wall = 1;
//             }
            
//             // printf("4\n");
//         }

//         if (cub3d->ray.side == 0)
//         {
//             cub3d->ray.perpwalldist = cub3d->ray.sidedistx - cub3d->ray.deltadistx;
//             // printf("1cube3d->screen_buffer.height: %d, cub3d->ray.perpwalldist: %f\n", cub3d->screen_buffer.height, cub3d->ray.perpwalldist);
//         }
//         else
//         {
//             cub3d->ray.perpwalldist = cub3d->ray.sidedisty - cub3d->ray.deltadisty;
//             // printf("2 cub3d->ray.perpwalldist (%f) = cub3d->ray.sidedisty (%f) - cub3d->ray.deltadisty (%f)\n", cub3d->ray.perpwalldist, cub3d->ray.sidedisty, cub3d->ray.deltadisty);
//         }
//         if (cub3d->ray.perpwalldist < 0.001)
//         {
//             cub3d->ray.perpwalldist += 0.001;
//             // printf("3cube3d->screen_buffer.height: %d, cub3d->ray.perpwalldist: %f\n", cub3d->screen_buffer.height, cub3d->ray.perpwalldist);
//         }
//         // printf("cube3d->screen_buffer.height: %d, cub3d->ray.perpwalldist: %f\n", cub3d->screen_buffer.height, cub3d->ray.perpwalldist);
//         // getchar();
//         cub3d->ray.lineheight = (int)(cub3d->screen_buffer.height / cub3d->ray.perpwalldist * 2);
//         cub3d->ray.drawstart = -cub3d->ray.lineheight / 2 + cub3d->screen_buffer.height / 2;
//         if (cub3d->ray.drawstart < 0)
//             cub3d->ray.drawstart = 0;
//         cub3d->ray.drawend = cub3d->ray.lineheight / 2 + cub3d->screen_buffer.height / 2;
//         if (cub3d->ray.drawend >= cub3d->screen_buffer.height)
//             cub3d->ray.drawend = cub3d->screen_buffer.height - 1;
        
//         ft_texture_helper(cub3d);
//         if (cub3d->ray.side == 0 && cub3d->ray.raydirx > 0)
//         {
//             ft_draw_wall_texture(cub3d, x, 0);
//             // printf("1 side\n");
//         }
//         else if (cub3d->ray.side == 0 && cub3d->ray.raydirx < 0)
//         {
//             ft_draw_wall_texture(cub3d, x, 1);
//             // printf("2 side\n");
//         }
//         else if (cub3d->ray.side == 1 && cub3d->ray.raydiry > 0)
//         {
//             ft_draw_wall_texture(cub3d, x, 2);
//             // printf("3 side\n");
//         }
//         else
//         {
//             ft_draw_wall_texture(cub3d, x, 3);
//             // printf("4 side\n");
//         }

// 		// ft_send_ray(cub3d, x);
// 		x++;
// 	}
// }