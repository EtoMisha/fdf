/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:04:01 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 18:45:06 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(t_point point0, t_point point1)
{
	if (point0.z > 0 || point1.z > 0)
		return (DEF_COLOR1);
	else
		return (DEF_COLOR0);
}

void	set_zoom(t_map *map, t_point *point0, t_point *point1)
{
	point0->x *= map->zoom;
	point0->y *= map->zoom;
	point0->z *= map->zoom;
	point1->x *= map->zoom;
	point1->y *= map->zoom;
	point1->z *= map->zoom;
}

void	set_isometry(t_map *map, t_point *point0, t_point *point1)
{
	int	prev_x;
	int	prev_y;

	if (map->iso_flag == 1)
	{
		prev_x = point0->x;
		prev_y = point0->y;
		point0->x = (prev_x - prev_y) * cos(map->angle);
		point0->y = -(point0->z) + (prev_x + prev_y) * sin(map->angle);
		prev_x = point1->x;
		prev_y = point1->y;
		point1->x = (prev_x - prev_y) * cos(map->angle);
		point1->y = -(point1->z) + (prev_x + prev_y) * sin(map->angle);
	}
}

void	set_rotation_z(t_map *map, t_point *point0, t_point *point1)
{
	int	prev_x;
	int	prev_y;

	prev_x = point0->x;
	prev_y = point0->y;
	point0->x = prev_x * cos(map->rotate_z) - prev_y * sin(map->rotate_z);
	point0->y = prev_x * sin(map->rotate_z) + prev_y * cos(map->rotate_z);
	prev_x = point1->x;
	prev_y = point1->y;
	point1->x = prev_x * cos(map->rotate_z) - prev_y * sin(map->rotate_z);
	point1->y = prev_x * sin(map->rotate_z) + prev_y * cos(map->rotate_z);
}

void	set_shift(t_map *map, t_point *point0, t_point *point1)
{
	point0->x += map->shift_x;
	point0->y += map->shift_y;
	point1->x += map->shift_x;
	point1->y += map->shift_y;
}
