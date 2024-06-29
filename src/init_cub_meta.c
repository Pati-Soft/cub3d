/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbasara <ahbasara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:23:39 by ahbasara          #+#    #+#             */
/*   Updated: 2024/06/29 04:18:44 by ahbasara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_value(t_cub3d *const cub3d, t_map_init *const map_init)
{
	map_init->key = get_key(map_init->buff);
	if (map_init->key == KEY_END)
		return (eerr(ERR_KEY));
	if (map_init->override[map_init->key])
		return (eerr(ERR_DUP_KEY));
	map_init->override[map_init->key] = 1;
	if (!ft_isspace(map_init->buff[map_init->lengths_key[map_init->key]]))
		return (eerr(ERR_NO_SPACE_SEPERATOR));
	map_init->trim_value = ft_strtrim(\
		map_init->buff + map_init->lengths_key[map_init->key], " \t\v\f\r\n");
	if (!map_init->trim_value)
		return (eerr(ERR_MALLOC));
	--map_init->meta_ct;
	printf("key: %d, value: %s\n", map_init->key, map_init->trim_value);
	if (map_init->meta_funcs[map_init->match_types[map_init->key]] \
		(cub3d, map_init))
		return (free(map_init->trim_value), FAILURE);
	if (map_init->meta_ct == 0)
		map_init->cont = 0;
	return (SUCCESS);
}

int	set_rgb(char const*const buff, unsigned int *const color)
{
	char		**split;
	int			arr[3];

	split = ft_split(buff, ',');
	if (!split)
		return (1);
	if (arrlen(split) != 3)
		return (free_2d(split), 1);
	if (ft_strsome(split[0], x_isdigit, NULL) || \
		ft_strsome(split[1], x_isdigit, NULL) || \
		ft_strsome(split[2], x_isdigit, NULL))
		return (free_2d(split), 1);
	arr[0] = ft_atoi(split[0]);
	arr[1] = ft_atoi(split[1]);
	arr[2] = ft_atoi(split[2]);
	free_2d(split);
	if (arr[0] > 255 || arr[1] > 255 || arr[2] > 255 || \
		arr[0] < 0 || arr[1] < 0 || arr[2] < 0)
		return (1);
	return (*color = (arr[0] << 16) | (arr[1] << 8) | (arr[2] << 0) | 0, 0);
}

t_return	set_color(t_cub3d *const cub3d, t_map_init *const map_init)
{
	if (set_rgb(map_init->trim_value,
			&cub3d->gradient[map_init->match_index[map_init->key]]))
		return (free(map_init->trim_value), eerr(ERR_WRONG_COLOR));
	ft_printf("val: %s\n", map_init->trim_value);
	free(map_init->trim_value);
	ft_printf("%d color: %d, %d, %d, %d\n",
		map_init->match_index[map_init->key],
		cub3d->gradient[map_init->match_index[map_init->key]] >> 24,
		(cub3d->gradient[map_init->match_index[map_init->key]] >> 16) & \
			0x000000ff,
		(cub3d->gradient[map_init->match_index[map_init->key]] >> 8) & \
			0x000000ff,
		(cub3d->gradient[map_init->match_index[map_init->key]] >> 0) & \
			0x000000ff);
	return (SUCCESS);
}

int	load_texture(t_cub3d *const cub3d, char *const path,
	t_direction const key)
{
	t_list	*idx_node;

	cub3d->textures[key].img = mlx_xpm_file_to_image(
			cub3d->mlx,
			path,
			&cub3d->textures[key].width,
			&cub3d->textures[key].height);
	free(path);
	if (cub3d->textures[key].img == NULL)
		return (eerr(ERR_TEX_OPEN));
	cub3d->textures[key].addr = (int *)mlx_get_data_addr(\
			cub3d->textures[key].img,
			&cub3d->textures[key].bits_per_pixel,
			&cub3d->textures[key].size_line,
			&cub3d->textures[key].endian);
	if (cub3d->textures[key].addr == NULL)
		return (eerr(ERR_TEX_OPEN));
	idx_node = ft_lstnew(cub3d->textures[key].img);
	if (idx_node == NULL)
		return (1);
	ft_lstadd_back(&cub3d->textures_success, idx_node);
	return (0);
}

t_return	set_texture(t_cub3d *const cub3d, t_map_init *const map_init)
{
	if (check_extension(map_init->trim_value, TEX_EXTENSION))
		return (free(map_init->trim_value), eerr(ERR_EXT_XPM));
	ft_printf("map path: %d %s %p\n",
		map_init->meta_ct, map_init->trim_value,
		(cub3d->textures)[map_init->meta_ct].img);
	if (load_texture(cub3d, map_init->trim_value,
			map_init->match_index[map_init->key]))
		return (FAILURE);
	return (SUCCESS);
}
