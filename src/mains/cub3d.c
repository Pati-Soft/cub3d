#include "cub3d.h"

__attribute__((destructor)) void	destructor(void)
{
	printf("Destructor called\n");
	// system("leaks cub3d");
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	t_cub3d	cub3d = {.map = (char *[])TEMPLE_MAP};

	if (init_cub3d(&cub3d))
		return (dealloc_cub3d(&cub3d), 1);
	printf("Hello, world!\n");
	return 0;
}
