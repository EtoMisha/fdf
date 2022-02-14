/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:26:57 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 18:45:39 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_img *img, float x, float y, int color)
{
	char	*dest;

	if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
	{
		dest = img->address + ((int)y * img->line_len + (int)x * img->bpp / 8);
		*(unsigned int *)dest = color;
	}
}

void	draw_line(t_map *map, t_img *img, t_point point0, t_point point1)
{
	float	d_x;
	float	d_y;
	float	d_color;
	float	steps;
	int		color;

	set_zoom(map, &point0, &point1);
	set_rotation_z(map, &point0, &point1);
	set_isometry(map, &point0, &point1);
	set_shift(map, &point0, &point1);
	d_x = point1.x - point0.x;
	d_y = point1.y - point0.y;
	steps = ft_max(ft_abs(d_x), ft_abs(d_y));
	d_x = d_x / steps;
	d_y = d_y / steps;
	color = point0.color;
	d_color = (point1.color - point0.color) / steps;
	while ((int)(point0.x - point1.x) || (int)(point0.y - point1.y))
	{
		draw_pixel(img, point0.x, point0.y, color);
		point0.x += d_x;
		point0.y += d_y;
		color += d_color;
	}
}

void	draw_outline(t_map *map, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	j = map->width - 1;
	while (i < map->height - 1)
	{
		draw_line(map, img, map->vertex[i][j], map->vertex[i + 1][j]);
		i++;
	}
	j = 0;
	while (j < map->width - 1)
	{
		draw_line(map, img, map->vertex[i][j], map->vertex[i][j + 1]);
		j++;
	}
}

void	draw_bg(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			draw_pixel(img, j, i, DEF_COLOR_BG);
			j++;
		}
		i++;
	}
}

void	draw_lines(t_map *map, t_img *img)
{
	int	i;
	int	j;

	draw_bg(img);
	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (j < map->width - 1)
		{
			draw_line(map, img, map->vertex[i][j], map->vertex[i][j + 1]);
			draw_line(map, img, map->vertex[i][j], map->vertex[i + 1][j]);
			j++;
		}
		i++;
	}
	draw_outline(map, img);
}
