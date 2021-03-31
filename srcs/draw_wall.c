/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:11:28 by obounri           #+#    #+#             */
/*   Updated: 2021/03/09 16:12:56 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void		init_t_wall(t_specs *specs, t_wall *wall, int i)
{
	init1(specs, wall, i);
	init2(specs, wall);
	hit_wall(specs, wall);
	if (wall->side == 0)
		wall->perpwalldist =
			(wall->map.x - specs->pos.x + (1 - wall->step.x) / 2)
			/ wall->raydir.x;
	else
		wall->perpwalldist =
			(wall->map.y - specs->pos.y + (1 - wall->step.y) / 2)
			/ wall->raydir.y;
	wall->lineheight = (int)(specs->ry / wall->perpwalldist);
	wall->drawstart = -wall->lineheight / 2 + specs->ry / 2;
	if (wall->drawstart < 0)
		wall->drawstart = 0;
	wall->drawend = wall->lineheight / 2 + specs->ry / 2;
	if (wall->drawend >= specs->ry)
		wall->drawend = specs->ry - 1;
	if (wall->side == 0)
		wall->wallx = specs->pos.y + wall->perpwalldist * wall->raydir.y;
	else
		wall->wallx = specs->pos.x + wall->perpwalldist * wall->raydir.x;
	wall->wallx -= floor((wall->wallx));
}

static void		floor_ceiling(int i, int drawstart, int drawend, t_specs *specs)
{
	int		y;

	if (drawend < drawstart)
	{
		drawstart += drawend;
		drawend = drawstart - drawend;
		drawstart -= drawend;
	}
	if (drawend < 0 || drawstart >= specs->ry || i < 0 || i >= specs->rx)
		return ;
	if (drawstart < 0)
		drawstart = 0;
	if (drawend >= specs->rx)
		drawend = specs->ry - 1;
	y = -1;
	while (++y < drawstart)
		specs->buff_data[i + (specs->rx * y)] = specs->ceiling;
	while (y <= drawend)
		y++;
	while (++y < specs->ry)
		specs->buff_data[i + (specs->rx * y)] = specs->floor;
}

static void		text_to_wall(t_specs *specs, t_wall *wall, int i)
{
	int y;

	y = wall->drawstart;
	while (y <= wall->drawend)
	{
		wall->tex.y = (int)wall->texpos & (TEX_HEIGHT - 1);
		wall->texpos += wall->iter;
		if (wall->side == 0 && specs->pos.x < wall->map.x)
			specs->buff_data[i + (specs->rx * y)] =
			specs->textures->textn_data[wall->tex.x + (wall->tex.y *
			TEX_WIDTH)];
		else if (wall->side == 0 && specs->pos.x >= wall->map.x)
			specs->buff_data[i + (specs->rx * y)] =
			specs->textures->texts_data[wall->tex.x + (wall->tex.y *
			TEX_WIDTH)];
		else if (wall->side == 1 && specs->pos.y < wall->map.y)
			specs->buff_data[i + (specs->rx * y)] =
			specs->textures->textw_data[wall->tex.x + (wall->tex.y *
			TEX_WIDTH)];
		else if (wall->side == 1 && specs->pos.y >= wall->map.y)
			specs->buff_data[i + (specs->rx * y)] =
			specs->textures->texte_data[wall->tex.x + (wall->tex.y *
			TEX_WIDTH)];
		y++;
	}
}

void			draw_wall(t_specs *specs)
{
	int		i;
	t_wall	wall;

	i = 0;
	while (i < specs->rx)
	{
		init_t_wall(specs, &wall, i);
		wall.tex.x = (int)(wall.wallx * (double)(TEX_WIDTH));
		if (wall.side == 0 && wall.raydir.x > 0)
			wall.tex.x = TEX_WIDTH - wall.tex.x - 1;
		if (wall.side == 1 && wall.raydir.y < 0)
			wall.tex.x = TEX_WIDTH - wall.tex.x - 1;
		wall.iter = 1.0 * TEX_HEIGHT / wall.lineheight;
		wall.texpos =
		(wall.drawstart - specs->ry / 2 + wall.lineheight / 2) * wall.iter;
		floor_ceiling(i, wall.drawstart, wall.drawend, specs);
		text_to_wall(specs, &wall, i);
		specs->z_buffer[i] = wall.perpwalldist;
		i++;
	}
}
