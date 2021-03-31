/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:27 by obounri           #+#    #+#             */
/*   Updated: 2021/03/08 16:00:59 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/includes/cub3d.h"

static void		rotate(int key, t_specs *specs)
{
	double olddirx;
	double oldplanex;

	if (key == RIGHT)
	{
		olddirx = specs->dir.x;
		specs->dir.x = specs->dir.x * cos(-ROT) - specs->dir.y * sin(-ROT);
		specs->dir.y = olddirx * sin(-ROT) + specs->dir.y * cos(-ROT);
		oldplanex = specs->plane.x;
		specs->plane.x =
		specs->plane.x * cos(-ROT) - specs->plane.y * sin(-ROT);
		specs->plane.y = oldplanex * sin(-ROT) + specs->plane.y * cos(-ROT);
	}
	else if (key == LEFT)
	{
		olddirx = specs->dir.x;
		specs->dir.x = specs->dir.x * cos(ROT) - specs->dir.y * sin(ROT);
		specs->dir.y = olddirx * sin(ROT) + specs->dir.y * cos(ROT);
		oldplanex = specs->plane.x;
		specs->plane.x = specs->plane.x * cos(ROT) - specs->plane.y * sin(ROT);
		specs->plane.y = oldplanex * sin(ROT) + specs->plane.y * cos(ROT);
	}
}

static void		move_up_down(int key, t_specs *specs)
{
	if (key == W_KEY)
	{
		if (specs->map[(int)(specs->pos.x + specs->dir.x * MOVESPEED)]
		[(int)(specs->pos.y)] == '0')
			specs->pos.x += specs->dir.x * MOVESPEED;
		if (specs->map[(int)(specs->pos.x)]
		[(int)(specs->pos.y + specs->dir.y * MOVESPEED)] == '0')
			specs->pos.y += specs->dir.y * MOVESPEED;
	}
	else if (key == S_KEY)
	{
		if (specs->map[(int)(specs->pos.x - specs->dir.x * MOVESPEED)]
		[(int)(specs->pos.y)] == '0')
			specs->pos.x -= specs->dir.x * MOVESPEED;
		if (specs->map[(int)(specs->pos.x)]
		[(int)(specs->pos.y - specs->dir.y * MOVESPEED)] == '0')
			specs->pos.y -= specs->dir.y * MOVESPEED;
	}
}

static void		move_right_left(int key, t_specs *specs)
{
	if (key == D_KEY)
	{
		if (specs->map[(int)(specs->pos.x + specs->plane.x * MOVESPEED)]
		[(int)(specs->pos.y)] == '0')
			specs->pos.x += specs->plane.x * MOVESPEED;
		if (specs->map[(int)(specs->pos.x)]
		[(int)(specs->pos.y + specs->plane.y * MOVESPEED)] == '0')
			specs->pos.y += specs->plane.y * MOVESPEED;
	}
	else if (key == A_KEY)
	{
		if (specs->map[(int)(specs->pos.x - specs->plane.x * MOVESPEED)]
		[(int)(specs->pos.y)] == '0')
			specs->pos.x -= specs->plane.x * MOVESPEED;
		if (specs->map[(int)(specs->pos.x)]
		[(int)(specs->pos.y - specs->plane.y * MOVESPEED)] == '0')
			specs->pos.y -= specs->plane.y * MOVESPEED;
	}
}

static int		key_hook(int key, t_specs *specs)
{
	if (key == ESC)
		destroy_exit(specs);
	else if (key == RIGHT || key == LEFT)
		rotate(key, specs);
	else if (key == W_KEY || key == S_KEY)
		move_up_down(key, specs);
	else if (key == D_KEY || key == A_KEY)
		move_right_left(key, specs);
	render_update(specs);
	return (0);
}

int				main(int ac, char **av)
{
	t_specs	specs;
	t_text	text;

	parser(ac, av, &specs);
	init_map(&specs);
	specs.textures = &text;
	init(&specs);
	mlx_hook((specs).mlx_win, 2, 0, key_hook, &specs);
	mlx_hook((specs).mlx_win, 17, 0, destroy_exit, &specs);
	mlx_loop((specs).mlx_ptr);
	return (0);
}
