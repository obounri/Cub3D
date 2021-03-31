/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:55:15 by obounri           #+#    #+#             */
/*   Updated: 2021/03/06 17:27:46 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	init_direction_ew(int a, int b, t_specs *specs)
{
	char c;

	c = specs->map[a][b];
	if (c == 'E')
	{
		specs->dir.x = 0;
		specs->dir.y = 1;
		specs->plane.x = 0.66;
		specs->plane.y = 0;
		specs->map[a][b] = '0';
	}
	else if (c == 'W')
	{
		specs->dir.x = 0;
		specs->dir.y = -1;
		specs->plane.x = -0.66;
		specs->plane.y = 0;
		specs->map[a][b] = '0';
	}
}

void		init_direction_ns(int a, int b, t_specs *specs)
{
	char c;

	c = specs->map[a][b];
	if (c == 'N')
	{
		specs->dir.x = -1;
		specs->dir.y = 0;
		specs->plane.x = 0;
		specs->plane.y = 0.66;
		specs->map[a][b] = '0';
	}
	else if (c == 'S')
	{
		specs->dir.x = 1;
		specs->dir.y = 0;
		specs->plane.x = 0;
		specs->plane.y = -0.66;
		specs->map[a][b] = '0';
	}
	init_direction_ew(a, b, specs);
}

void		init1(t_specs *specs, t_wall *wall, int i)
{
	wall->camerax = 2 * i / (double)specs->rx - 1;
	wall->raydir.x = specs->dir.x + specs->plane.x * wall->camerax;
	wall->raydir.y = specs->dir.y + specs->plane.y * wall->camerax;
	wall->map.x = (int)(specs->pos.x);
	wall->map.y = (int)(specs->pos.y);
	wall->deltadist.x = fabs(1 / wall->raydir.x);
	wall->deltadist.y = fabs(1 / wall->raydir.y);
	wall->hit = 0;
}

void		init2(t_specs *specs, t_wall *wall)
{
	if (wall->raydir.x < 0)
	{
		wall->step.x = -1;
		wall->sidedist.x = (specs->pos.x - wall->map.x) * wall->deltadist.x;
	}
	else
	{
		wall->step.x = 1;
		wall->sidedist.x = (wall->map.x + 1.0 - specs->pos.x) *
		wall->deltadist.x;
	}
	if (wall->raydir.y < 0)
	{
		wall->step.y = -1;
		wall->sidedist.y = (specs->pos.y - wall->map.y) * wall->deltadist.y;
	}
	else
	{
		wall->step.y = 1;
		wall->sidedist.y = (wall->map.y + 1.0 - specs->pos.y) *
		wall->deltadist.y;
	}
}

void		hit_wall(t_specs *specs, t_wall *wall)
{
	while (wall->hit == 0)
	{
		if (wall->sidedist.x < wall->sidedist.y)
		{
			wall->sidedist.x += wall->deltadist.x;
			wall->map.x += wall->step.x;
			wall->side = 0;
		}
		else
		{
			wall->sidedist.y += wall->deltadist.y;
			wall->map.y += wall->step.y;
			wall->side = 1;
		}
		if (specs->map[wall->map.x][wall->map.y] == '1')
			wall->hit = 1;
	}
}
