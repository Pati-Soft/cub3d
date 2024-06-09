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

int main(int argc, char const *argv[])
{
	t_cub3d	* const cub3d = &(t_cub3d){0};

	(void)argc;
	MURMURTEST
	if (argc != 2)
		return (err(ERR_PREFIX), err(ERR_ARGC));
	*((char **)&cub3d->map_name) = (char *)argv[1];
	*(char ***)&cub3d->map = (char *[])TEMPLE_MAP;

	if (init_cub3d(cub3d))
		return (dealloc_cub3d(cub3d), 1);
	// ray_cast(cub3d);
	printf("Hello, world!\n");
	return 0;
}
