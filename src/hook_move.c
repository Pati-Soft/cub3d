/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:18:19 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 20:26:46 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_character(char const c)
{
	if (c == NORTH_CHAR || c == SOUTH_CHAR
		|| c == EAST_CHAR || c == WEST_CHAR)
		return (1);
	return (0);
}

void	key_w(t_cub3d *const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.\
		dirx * MOVEMENT_SPEED))-> content)[(int)(cub3d->player.posy)] == '0'\
		|| is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx \
		+ cub3d->player.dirx * MOVEMENT_SPEED))->content)[(int)(cub3d->player.\
		posy)]))
		cub3d->player.posx += cub3d->player.dirx * MOVEMENT_SPEED;
	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
		cub3d->player.posy + cub3d->player.diry * MOVEMENT_SPEED)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->\
		content)[(int)(cub3d->player.posy + cub3d->player.diry * \
		MOVEMENT_SPEED)]))
		cub3d->player.posy += cub3d->player.diry * MOVEMENT_SPEED;
}

void	key_s(t_cub3d *const cub3d)
{
	if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.\
		dirx * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - \
		cub3d->player.dirx * MOVEMENT_SPEED)))[(int)(cub3d->player.posy)]))
		cub3d->player.posx -= cub3d->player.dirx * MOVEMENT_SPEED;
	if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
		cub3d->player.posy - cub3d->player.diry * MOVEMENT_SPEED)] == '0' || \
		is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx))[(\
		int)(cub3d->player.posy - cub3d->player.diry * MOVEMENT_SPEED)]))
		cub3d->player.posy -= cub3d->player.diry * MOVEMENT_SPEED;
}

// void	key_d(t_cub3d *const cub3d)
// {
// 	if (data->map->map[(int)(data->ray->posx + data->ray->diry
// 			* 0.15)][(int)(data->ray->posy)] == '0'
// 		|| is_character(data->map->map[(int)(data->ray->posx + data->ray->diry
// 				* 0.15)][(int)(data->ray->posy)]))
// 		data->ray->posx += data->ray->diry * 0.15;
// 	if (data->map->map[(int)(data->ray->posx)][(int)(data->ray->posy
// 			- data->ray->dirx * 0.15)] == '0'
// 		|| is_character(data->map->map[(int)(data->ray->posx)]
// 		[(int)(data->ray->posy - data->ray->dirx * 0.15)]))
// 		data->ray->posy -= data->ray->dirx * 0.15;
// }

// void	key_a(t_cub3d *const cub3d)
// {
// 	// ((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.diry * MOVEMENT_SPEED))->content)
// 	if (data->map->map[(int)(data->ray->posx - data->ray->diry
// 			* 0.15)][(int)(data->ray->posy)] == '0'
// 		|| is_character(data->map->map[(int)(data->ray->posx - data->ray->diry
// 				* 0.15)][(int)(data->ray->posy)]))
// 		data->ray->posx -= data->ray->diry * 0.15;
// 	if (data->map->map[(int)(data->ray->posx)][(int)(data->ray->posy
// 			+ data->ray->dirx * 0.15)] == '0'
// 		|| is_character(data->map->map[(int)(data->ray->posx)]
// 		[(int)(data->ray->posy + data->ray->dirx * 0.15)]))
// 		data->ray->posy += data->ray->dirx * 0.15;
// }

void	key_a(t_cub3d *const cub3d)
{
	move_horizontal_left(cub3d, cub3d->player.dirx, cub3d->player.diry);
	// if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - cub3d->player.\
	// 	diry * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0' || \
	// 	is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx - \
	// 	cub3d->player.diry * MOVEMENT_SPEED))->content)[(int)(cub3d->player.\
	// 	posy)]))
	// 	cub3d->player.posx -= cub3d->player.diry * MOVEMENT_SPEED;
	// if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
	// 	cub3d->player.posy + cub3d->player.dirx * MOVEMENT_SPEED)] == '0' || \
	// 	is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->\
	// 	content)[(int)(cub3d->player.posy + cub3d->player.dirx * \
	// 	MOVEMENT_SPEED)]))
	// 	cub3d->player.posy += cub3d->player.dirx * MOVEMENT_SPEED;
}

void	key_d(t_cub3d *const cub3d)
{
	move_horizontal_right(cub3d, cub3d->player.dirx, cub3d->player.diry);
	// if (((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + cub3d->player.\
	// 	diry * MOVEMENT_SPEED))->content)[(int)(cub3d->player.posy)] == '0' || \
	// 	is_character(((char *)ll_nod(cub3d->map2, (int)(cub3d->player.posx + \
	// 	cub3d->player.diry * MOVEMENT_SPEED))->content)[(int)(cub3d->player.\
	// 	posy)]))
	// 	cub3d->player.posx += cub3d->player.diry * MOVEMENT_SPEED;
	// if (((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->content)[(int)(\
	// 	cub3d->player.posy - cub3d->player.dirx * MOVEMENT_SPEED)] == '0' || \
	// 	is_character(((char *)ll_nod(cub3d->map2, (int)cub3d->player.posx)->\
	// 	content)[(int)(cub3d->player.posy - cub3d->player.dirx * \
	// 	MOVEMENT_SPEED)]))
	// 	cub3d->player.posy -= cub3d->player.dirx * MOVEMENT_SPEED;
}
#include <math.h>

void move_horizontal_right(t_cub3d *game, double dirx, double diry)
{
    t_player *player = &game->player;

    // Yön açısını hesapla (oyuncunun baktığı açı)
    double angle = atan2(diry, dirx);
    angle -= M_PI / 2;

    // Yeni yön vektörünü hesapla
    double new_dirx = cos(angle);
    double new_diry = sin(angle);

    // Hareket miktarını hesapla
    double move_x = new_dirx * MOVEMENT_SPEED;
    double move_y = new_diry * MOVEMENT_SPEED;

    // Oyuncu pozisyonunu güncelle
    player->posx += move_x;
    player->posy += move_y;

	printf("player: x: %lf, y: %lf, direction: %d\n", game->player.posx, game->player.posy, game->player.direction);
    // Burada, çarpışma kontrolü yapılabilir
    // Eğer çarpışma varsa, oyuncunun pozisyonunu eski konumuna geri alabilirsiniz.
    // Örneğin:
    // double old_x = player->posx;
    // double old_y = player->posy;
    // if (collision_detected(player)) {
    //     player->posx = old_x;
    //     player->posy = old_y;
    // }
}

#include <math.h>

void move_horizontal_left(t_cub3d *game, double dirx, double diry)
{
    t_player *player = &game->player;

    // Yön açısını hesapla (oyuncunun baktığı açı)
    double angle = atan2(diry, dirx);

    // 90 derece sola döndür
    angle += M_PI / 2;

    // Yeni yön vektörünü hesapla
    double new_dirx = cos(angle);
    double new_diry = sin(angle);

    // Hareket miktarını hesapla
    double move_x = new_dirx * MOVEMENT_SPEED;
    double move_y = new_diry * MOVEMENT_SPEED;

    // Oyuncu pozisyonunu güncelle
    player->posx += move_x;
    player->posy += move_y;

	printf("player: x: %lf, y: %lf, direction: %d\n", game->player.posx, game->player.posy, game->player.direction);
    // Burada, çarpışma kontrolü yapılabilir
    // Eğer çarpışma varsa, oyuncunun pozisyonunu eski konumuna geri alabilirsiniz.
    // Örneğin:
    // double old_x = player->posx;
    // double old_y = player->posy;
    // if (collision_detected(player)) {
    //     player->posx = old_x;
    //     player->posy = old_y;
    // }
}
