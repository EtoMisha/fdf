/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:04:36 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 21:05:32 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_settings(t_map *map)
{
	map->angle = DEF_ANGLE;
	map->def_zoom = ft_max(WIN_WIDTH / map->width * 0.5, 0.1);
	map->zoom = 1;
	map->iso_flag = 1;
	map->rotate_z = DEF_ROTATE_Z;
	map->shift_x = (WIN_WIDTH - map->width * map->def_zoom);
	map->shift_y = (WIN_HEIGHT - map->height * map->def_zoom) / 2;
}

int	key_hook(int key_code, t_mlx_vars *vars)
{
	if (key_code <= 126 && key_code >= 123)
		hook_move(key_code, vars);
	else if ((key_code >= 0 && key_code <= 2) || key_code == 13)
		hook_zoom_rotate(key_code, vars);
	else if (key_code >= 18 && key_code <= 20)
		hook_views(key_code, vars);
	else if (key_code == 53)
		hook_exit(vars);
	else
		return (1);
	remake_image(vars);
	return (1);
}

void	draw(t_map *map, t_img *img, t_mlx_vars *vars)
{
	vars->mlx = mlx_init();
	vars->mlx_window = mlx_new_window(vars->mlx, \
		WIN_WIDTH, WIN_HEIGHT, "My beautiful fdf window");
	img->ptr = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->address = mlx_get_data_addr(img->ptr, \
		&img->bpp, &img->line_len, &img->endian);
	draw_lines(map, img);
	mlx_put_image_to_window(vars->mlx, vars->mlx_window, img->ptr, 0, 0);
	mlx_hook(vars->mlx_window, 2, (1L << 0), key_hook, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_img		img;
	t_mlx_vars	vars;

	if (argc != 2)
		return (exit_w_error("Invalid arguments\n", &map, 0));
	if (count_size(argv[1], &map) == 0)
		return (exit_w_error("Error while reading map\n", &map, 0));
	map_settings(&map);
	if (read_map(argv[1], &map) == 0)
		return (exit_w_error("Error while saving map\n", &map, 1));
	vars.map = &map;
	vars.img = &img;
	draw(&map, &img, &vars);
}
