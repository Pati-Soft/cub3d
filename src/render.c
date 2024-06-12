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