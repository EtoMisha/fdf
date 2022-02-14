/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:03:17 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 21:17:50 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	remake_image(t_mlx_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	vars->img->ptr = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img->address = mlx_get_data_addr(vars->img->ptr, \
		&vars->img->bpp, &vars->img->line_len, &vars->img->endian);
	draw_lines(vars->map, vars->img);
	mlx_put_image_to_window(vars->mlx, vars->mlx_window, vars->img->ptr, 0, 0);
}

void	hook_exit(t_mlx_vars *vars)
{
	ft_putstr_fd("Exit\n", 1);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	mlx_destroy_window(vars->mlx, vars->mlx_window);
	free_map(vars->map);
	exit(1);
}

void	hook_move(int key_code, t_mlx_vars *vars)
{
	if (key_code == 123)
	{
		vars->map->shift_x += SHIFT_STEP;
		ft_putstr_fd("Move left\n", 1);
	}
	else if (key_code == 124)
	{
		vars->map->shift_x -= SHIFT_STEP;
		ft_putstr_fd("Move right\n", 1);
	}
	else if (key_code == 125)
	{
		vars->map->shift_y -= SHIFT_STEP;
		ft_putstr_fd("Move down\n", 1);
	}
	else if (key_code == 126)
	{
		vars->map->shift_y += SHIFT_STEP;
		ft_putstr_fd("Move up\n", 1);
	}
}

void	hook_zoom_rotate(int key_code, t_mlx_vars *vars)
{
	if (key_code == 13 && vars->map->zoom < 10)
	{
		vars->map->zoom += ZOOM_STEP;
		ft_putstr_fd("Zoom in\n", 1);
	}
	else if (key_code == 1 && vars->map->zoom > 2 * ZOOM_STEP)
	{
		vars->map->zoom -= ZOOM_STEP;
		ft_putstr_fd("Zoom out\n", 1);
	}
	else if (key_code == 0)
	{
		vars->map->rotate_z -= ROTATE_STEP;
		ft_putstr_fd("Rotate left\n", 1);
	}
	else if (key_code == 2)
	{
		vars->map->rotate_z += ROTATE_STEP;
		ft_putstr_fd("Rotate right\n", 1);
	}
}

void	hook_views(int key_code, t_mlx_vars *vars)
{
	vars->map->shift_x = (WIN_WIDTH - \
		vars->map->width * vars->map->def_zoom);
	vars->map->shift_y = (WIN_HEIGHT - \
		vars->map->height * vars->map->def_zoom) / 2;
	vars->map->zoom = 1;
	vars->map->rotate_z = DEF_ROTATE_Z;
	vars->map->iso_flag = 1;
	if (key_code == 18)
	{
		vars->map->angle = DEF_ANGLE;
		ft_putstr_fd("Default isometric view\n", 1);
	}
	else if (key_code == 19)
	{
		vars->map->iso_flag = 0;
		vars->map->rotate_z = 0;
		ft_putstr_fd("Flat view\n", 1);
	}
	else if (key_code == 20)
	{
		vars->map->angle = 0;
		ft_putstr_fd("Side view\n", 1);
	}
}
