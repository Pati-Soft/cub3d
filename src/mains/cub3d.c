#include "cub3d.h"
#include "murmur_eval.h"

__attribute__((destructor)) void	destructor(void)
{
	printf("Destructor called\n");
	// system("leaks cub3d");
}

int main(int argc, char const *argv[])
{
	(void)argc;
	MURMURTEST

	if (argc != 2)
		return (err(ERR_PREFIX), err(ERR_ARGC));
	t_cub3d	* const cub3d = &(t_cub3d){0};
	*((char **)&cub3d->map_name) = (char *)argv[1];
	*(char ***)&cub3d->map = (char *[])TEMPLE_MAP;

	if (init_cub3d(cub3d))
		return (dealloc_cub3d(cub3d), 1);
	printf("Hello, world!\n");
	return 0;
}
