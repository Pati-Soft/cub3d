#include "cub3d.h"

void	ft_fill_floor_and_ceiling(t_cub3d *cub3d)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < cub3d->screen_buffer.height / 2)
	{
		n = 0;
		while (n < cub3d->screen_buffer.width)
		{
			cub3d->screen_buffer.addr[i * cub3d->screen_buffer.width + n] = cub3d->floor_ceiling[0];
			n++;
		}
		i++;
	}
	while (i < cub3d->screen_buffer.height)
	{
		n = 0;
		while (n < cub3d->screen_buffer.width)
		{
			cub3d->screen_buffer.addr[i * cub3d->screen_buffer.width + n] = cub3d->floor_ceiling[1];
			n++;
		}
		i++;
	}
}

int	loop(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	ft_printf("loop\n");
	ft_fill_floor_and_ceiling(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win_mlx, cub3d->screen_buffer.img, 0, 0);
	// ft_move(cub3d);
	// ft_ray_casting(cub3d);
	// mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, cub3d->mlx_img, 0, 0);
	return (0);
}