/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:18:40 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 21:15:09 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_width(char *map_str)
{
	int	count;

	count = 0;
	while (*map_str)
	{
		while (*map_str == ' ' && *map_str)
			map_str++;
		if (*map_str != ' ' && *map_str != '\n' && *map_str)
			count++;
		while (*map_str != ' ' && *map_str)
			map_str++;
	}
	return (count);
}

int	count_size(char *filename, t_map *map)
{
	int		fd;
	char	*map_str;
	int		check_read;
	int		line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	check_read = 1;
	line_count = 0;
	while (check_read)
	{
		check_read = get_next_line(fd, &map_str);
		if (check_read < 0)
			return (0);
		if (line_count == 0)
			map->width = count_width(map_str);
		if (check_read > 0)
			line_count++;
		free(map_str);
	}
	close(fd);
	map->height = line_count;
	return (1);
}

int	save_color(char *str, int z)
{
	int	color;

	while (ft_isdigit(*str) && *str)
		str++;
	if (*str == ',' && *str)
	{
		str += 1;
		color = ft_atoi16(str);
	}
	else if (z == 0)
		color = DEF_COLOR0;
	else if (z > 0)
		color = DEF_COLOR1;
	else
		color = DEF_COLOR2;
	return (color);
}

int	save_line(t_map *map, char *map_str, int line_number)
{
	int	i;

	i = 0;
	map->vertex[line_number] = malloc(sizeof(t_point) * map->width);
	if (map->vertex[line_number] == NULL)
		return (0);
	while (i < map->width)
	{
		while (*map_str == ' ' && *map_str)
			map_str++;
		(map->vertex[line_number][i]).x = i * map->def_zoom;
		(map->vertex[line_number][i]).y = line_number * map->def_zoom;
		(map->vertex[line_number][i]).z = \
			ft_atoi(map_str) * map->def_zoom / Z_HEIGHT;
		(map->vertex[line_number][i]).color = save_color(map_str, \
			(map->vertex[line_number][i]).z);
		while (*map_str != ' ' && *map_str)
			map_str++;
		while (*map_str == ' ' && *map_str)
			map_str++;
		i++;
	}
	return (i);
}

int	read_map(char *filename, t_map *map)
{
	int		fd;
	char	*map_str;
	int		check_read;
	int		line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	check_read = 1;
	line_count = 0;
	map->vertex = malloc(sizeof(t_point *) * map->height);
	while (line_count < map->height)
	{
		check_read = get_next_line(fd, &map_str);
		if (check_read < 0)
			return (exit_w_free(&map_str, map));
		if (save_line(map, map_str, line_count) == 0)
			return (exit_w_error("Malloc error\n", map, 0));
		free(map_str);
		line_count++;
	}
	close(fd);
	return (line_count);
}
