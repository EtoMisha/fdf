/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:17:58 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/12 17:16:31 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->vertex[i]);
		i++;
	}
	free(map->vertex);
}

int	exit_w_error(char *msg, t_map *map, int need_free)
{
	ft_putstr_fd(msg, 2);
	if (need_free == 1)
		free_map(map);
	return (0);
}

int	exit_w_free(char **map_str, t_map *map)
{
	free(*map_str);
	free(map->vertex);
	return (0);
}

float	ft_abs(float x)
{
	if (x >= 0)
		return (x);
	else
		return (-x);
}

float	ft_max(float x1, float x2)
{
	if (x1 > x2)
		return (x1);
	else
		return (x2);
}
