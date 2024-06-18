#include "cub3d.h"

void	ft_fill_floor_and_ceiling(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < WIN_HEIGHT / 2)
	{
		n = 0;
		while (n < WIN_WIDTH)
		{
			data->mlx_o_data[i * WIN_WIDTH + n] = data->map->ceiling_color;
			n++;
		}
		i++;
	}
	while (i < WIN_HEIGHT)
	{
		n = 0;
		while (n < WIN_WIDTH)
		{
			data->mlx_o_data[i * WIN_WIDTH + n] = data->map->floor_color;
			n++;
		}
		i++;
	}
}

int	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_fill_floor_and_ceiling(data);
	ft_move(data);
	ft_ray_casting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->mlx_img, 0, 0);
	return (0);
}