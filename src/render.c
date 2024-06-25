#include "cub3d.h"

void	ft_texture_helper(t_cub3d * const cub3d)
{
	double	wallx;

	if (cub3d->ray.side == 0)
		wallx = cub3d->player.posy + cub3d->ray.perpwalldist * cub3d->ray.raydiry;
	else
		wallx = cub3d->player.posx + cub3d->ray.perpwalldist * cub3d->ray.raydirx;
	wallx -= floor(wallx);
	cub3d->ray.tex_x = (int)(wallx * (double)RESULATION);
	if (cub3d->ray.side == 0 && cub3d->ray.raydirx > 0)
		cub3d->ray.tex_x = RESULATION - cub3d->ray.tex_x - 1;
	if (cub3d->ray.side == 1 && cub3d->ray.raydiry < 0)
		cub3d->ray.tex_x = RESULATION - cub3d->ray.tex_x - 1;
	cub3d->ray.texstep = 1.0 * RESULATION / cub3d->ray.lineheight;
	printf("step: %f\n", cub3d->ray.texstep);
	cub3d->ray.texpos = (cub3d->ray.drawstart - cub3d->screen_buffer.height
			/ 2 + cub3d->ray.lineheight / 2) * cub3d->ray.texstep;
}

void	ft_draw_wall_texture(t_cub3d * const cub3d, int const x, int const tex_index)
{
	int			texy;
	// double		bak2 = cub3d->ray.texpos;
	// int const	bak[3] = {cub3d->ray.drawstart, cub3d->ray.drawend};
	while (cub3d->ray.drawstart < cub3d->ray.drawend)
	{
		// ft_printf("[DEBUG]: drawing");
		texy = (int)cub3d->ray.texpos & (RESULATION - 1);
		// printf("texpos: %f\n", cub3d->ray.texpos);
		cub3d->ray.texpos += cub3d->ray.texstep;
		if (cub3d->textures[tex_index].addr[RESULATION * texy + cub3d->ray.tex_x] > 0)
		{
			cub3d->screen_buffer.addr[cub3d->ray.drawstart * cub3d->screen_buffer.width + x]
				= cub3d->textures[tex_index].addr[RESULATION * texy + cub3d->ray.tex_x];
			// printf("x: %d, y: %d\n", cub3d->ray.tex_x, texy);
		}
		cub3d->ray.drawstart++;
	}
	// printf("texpos: (%f) drawstart: (%d), drawend: (%d), diff: (%d), ratio: (diff/64=%f)\n", bak2, bak[0], bak[1], bak[1] - bak[0], (float)abs(bak[1] - bak[0]) / RESULATION);
	// getchar();
	// mlx_put_image_to_window(cub3d->mlx, cub3d->win_mlx, cub3d->screen_buffer.img, 0, 0);
	// mlx_do_sync(cub3d->mlx);

}

void	ft_draw_wall_side(t_cub3d * const cub3d, int const x)
{
	ft_texture_helper(cub3d);
	if (cub3d->ray.side == 0 && cub3d->ray.raydirx > 0)
	{
		ft_draw_wall_texture(cub3d, x, 0);
		// printf("1 side\n");
	}
	else if (cub3d->ray.side == 0 && cub3d->ray.raydirx < 0)
	{
		ft_draw_wall_texture(cub3d, x, 1);
		// printf("2 side\n");
	}
	else if (cub3d->ray.side == 1 && cub3d->ray.raydiry > 0)
	{
		ft_draw_wall_texture(cub3d, x, 2);
		// printf("3 side\n");
	}
	else
	{
		ft_draw_wall_texture(cub3d, x, 3);
		// printf("4 side\n");
	}
}

void	ft_direction(t_cub3d * const cub3d)
{
	if (cub3d->ray.raydirx < 0)
	{
		cub3d->ray.stepx = -1;
		cub3d->ray.sidedistx = (cub3d->player.posx - cub3d->ray.map_y)
			* cub3d->ray.deltadistx;
	}
	else
	{
		cub3d->ray.stepx = 1;
		cub3d->ray.sidedistx = (cub3d->ray.map_y + 1.0 - cub3d->player.posx)
			* cub3d->ray.deltadistx;
	}
	if (cub3d->ray.raydiry < 0)
	{
		cub3d->ray.stepy = -1;
		cub3d->ray.sidedisty = (cub3d->player.posy - cub3d->ray.map_x)
			* cub3d->ray.deltadisty;
	}
	else
	{
		cub3d->ray.stepy = 1;
		cub3d->ray.sidedisty = (cub3d->ray.map_x + 1.0 - cub3d->player.posy)
			* cub3d->ray.deltadisty;
	}
}

void	ft_wallhit(t_cub3d * const cub3d)
{
	cub3d->ray.wall = 0;
	while (!cub3d->ray.wall)
	{
		if (cub3d->ray.sidedistx < cub3d->ray.sidedisty)
		{
		// printf("1\n");
			cub3d->ray.sidedistx += cub3d->ray.deltadistx;
			cub3d->ray.map_y += cub3d->ray.stepx;
			cub3d->ray.side = 0;
		}
		else
		{
		// printf("2\n");
			cub3d->ray.sidedisty += cub3d->ray.deltadisty;
			cub3d->ray.map_x += cub3d->ray.stepy;
			cub3d->ray.side = 1;
		}
		// printf("3\n");
		// printf("cub3d->ray.map_y: %d, cub3d->ray.map_x: %d\n", cub3d->ray.map_y, cub3d->ray.map_x);
		// ((char *)ll_nod(cub3d->map2, cub3d->ray.map_y)->content)[cub3d->ray.map_x] = 'X';
		// pm(cub3d);
		// printf("map2\n");
		if (((char *)ll_nod(cub3d->map2, cub3d->ray.map_y)->content) \
			[cub3d->ray.map_x] == WALL_CHAR)
		{
			cub3d->ray.wall = 1;
		}
		
		// printf("4\n");
	}
	// exit(0);
}

void	ft_raydist(t_cub3d * const cub3d)
{
	if (cub3d->ray.side == 0)
	{
		cub3d->ray.perpwalldist = cub3d->ray.sidedistx - cub3d->ray.deltadistx;
		// printf("1cube3d->screen_buffer.height: %d, cub3d->ray.perpwalldist: %f\n", cub3d->screen_buffer.height, cub3d->ray.perpwalldist);
	}
	else
	{
		cub3d->ray.perpwalldist = cub3d->ray.sidedisty - cub3d->ray.deltadisty;
		// printf("2 cub3d->ray.perpwalldist (%f) = cub3d->ray.sidedisty (%f) - cub3d->ray.deltadisty (%f)\n", cub3d->ray.perpwalldist, cub3d->ray.sidedisty, cub3d->ray.deltadisty);
	}
	if (cub3d->ray.perpwalldist < 0.001)
	{
		cub3d->ray.perpwalldist += 0.001;
		// printf("3cube3d->screen_buffer.height: %d, cub3d->ray.perpwalldist: %f\n", cub3d->screen_buffer.height, cub3d->ray.perpwalldist);
	}
	// printf("cube3d->screen_buffer.height: %d, cub3d->ray.perpwalldist: %f\n", cub3d->screen_buffer.height, cub3d->ray.perpwalldist);
	// getchar();
	cub3d->ray.lineheight = (int)(cub3d->screen_buffer.height / cub3d->ray.perpwalldist * 2);
	cub3d->ray.drawstart = -cub3d->ray.lineheight / 2 + cub3d->screen_buffer.height / 2;
	if (cub3d->ray.drawstart < 0)
		cub3d->ray.drawstart = 0;
	cub3d->ray.drawend = cub3d->ray.lineheight / 2 + cub3d->screen_buffer.height / 2;
	if (cub3d->ray.drawend >= cub3d->screen_buffer.height)
		cub3d->ray.drawend = cub3d->screen_buffer.height - 1;
}

void	ft_send_ray(t_cub3d * const cub3d, int const x)
{
	// printf("ft_direction %d / %d\n", x, cub3d->screen_buffer.width);
	ft_direction(cub3d);
	// printf("ft_wallhit %d / %d\n", x, cub3d->screen_buffer.width);
	ft_wallhit(cub3d);
	// printf("ft_raydist %d / %d\n", x, cub3d->screen_buffer.width);
	ft_raydist(cub3d);
	// printf("ft_draw_wall_side %d / %d\n", x, cub3d->screen_buffer.width);
	ft_draw_wall_side(cub3d, x);
}

void	ft_ray_casting(t_cub3d * const cub3d)
{
	int			x;

	x = 0;
	while (x < cub3d->screen_buffer.width)
	{
		// printf("an unnamed ray %d / %d\n", x, cub3d->screen_buffer.width);
		cub3d->ray.camerax = (double)x / (cub3d->screen_buffer.width - 1);  // Ekran genişliğine orantılı
		cub3d->ray.raydirx = cub3d->player.dirx + (cub3d->ray.planex * (cub3d->ray.camerax - 0.5) * 2); // Orta noktayı 0.5 yapar
		cub3d->ray.raydiry = cub3d->player.diry + (cub3d->ray.planey * (cub3d->ray.camerax - 0.5) * 2); // Orta noktayı 0.5 yapar
		cub3d->ray.map_y = (int)cub3d->player.posx;
		cub3d->ray.map_x = (int)cub3d->player.posy;
		// printf("posx: %f, posy: %f\n", cub3d->player.posx, cub3d->player.posy);
		cub3d->ray.deltadistx = fabs(1 / cub3d->ray.raydirx);
		cub3d->ray.deltadisty = fabs(1 / cub3d->ray.raydiry);
		// printf("000 cub3d->ray.perpwalldist (%f) = cub3d->ray.sidedisty (%f) - cub3d->ray.deltadisty (%f)\n", cub3d->ray.perpwalldist, cub3d->ray.sidedisty, cub3d->ray.deltadisty);
		ft_send_ray(cub3d, x);
		// printf("sended ray %d / %d\n", x, cub3d->screen_buffer.width);
		x++;
	}
}

void	ft_fill_floor_and_ceiling(t_cub3d * const cub3d)
{
	int	i;
	int	n;

	i = -1;
	while (++i < cub3d->screen_buffer.height / 2)
	{
		n = -1;
		while (++n < cub3d->screen_buffer.width)
			cub3d->screen_buffer.addr[i * cub3d->screen_buffer.width + n] = \
			cub3d->floor_ceiling[0];
	}
	while (++i < cub3d->screen_buffer.height)
	{
		n = -1;
		while (++n < cub3d->screen_buffer.width)
			cub3d->screen_buffer.addr[i * cub3d->screen_buffer.width + n] = \
			cub3d->floor_ceiling[1];
	}
}

int	loop(void * const param)
{
	t_cub3d	* const cub3d = (t_cub3d *)param;

	// ft_printf("loop\n");
	ft_fill_floor_and_ceiling(cub3d);
	// mlx_do_sync(cub3d->mlx);
	// printf("perpwalldist: %f\n", cub3d->ray.perpwalldist);
	ft_player_move(cub3d);
	ft_ray_casting(cub3d);
	// mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->mlx_img, 0, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win_mlx, cub3d->screen_buffer.img, 0, 0);
	return (0);
}