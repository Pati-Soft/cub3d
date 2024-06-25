#include "cub3d.h"
#include "murmur_eval.h"

__attribute__((destructor)) void	destructor(void)
{
	printf("Destructor called\n");
	// system("leaks cub3d");
}
// static void	ray_cast(t_cub3d * const cub3d)
// {
// 	double	h_inter;
// 	double	v_inter;
// 	int		angle;
// 	int		ray;

// 	ray = 0;
// 	angle = cub3d->player.direction - (FOV / 2);
// 	while (ray < WIN_WIDTH)
// 	{
// 		h_inter = horizontal_intercept(cub3d, ray);
// 		v_inter = vertical_intercept(cub3d, ray);
// 		if (h_inter < v_inter)
// 			draw_ray(cub3d, h_inter, ray, 0);
// 		else
// 			draw_ray(cub3d, v_inter, ray, 1);
// 		ray++;
// 	}
// }

void	init_variable(t_cub3d * const cub3d, int argc, char const *argv[])
{
	*((char **)&cub3d->map_name) = (char *)argv[argc - 1];
	cub3d->ray.deltadistx = 0;
	cub3d->ray.deltadisty = 0;
	cub3d->ray.perpwalldist = 0;
	cub3d->ray.stepx = 0;
	cub3d->ray.stepy = 0;
	cub3d->ray.sidedistx = 0;
	cub3d->ray.sidedisty = 0;
	cub3d->ray.map_x = 0;
	cub3d->ray.map_y = 0;
	cub3d->ray.side = 0;
	cub3d->ray.wall = 0;
	cub3d->ray.raydirx = 0;
	cub3d->ray.raydiry = 0;
}

int main(int argc, char const *argv[])
{
	t_cub3d	* const cub3d = &(t_cub3d){0};
	// bzero(cub3d, sizeof(t_cub3d)); // safe free

	init_variable(cub3d, argc, argv);
	MURMURTEST
	if (argc != 2)
		return (eerr(ERR_ARGC));
	if (init_cub3d(cub3d))
		return (dealloc_cub3d(cub3d), 1);
	mlx_loop(cub3d->mlx);
	return 0;
}
