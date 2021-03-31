/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:42 by obounri           #+#    #+#             */
/*   Updated: 2021/03/08 16:41:29 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	sort_sprites(t_specs *specs)
{
	int		i;
	int		j;
	int		v;
	int		z;

	i = 1;
	j = 0;
	while (i < specs->num_prites)
	{
		v = specs->sprite_distance[i];
		z = specs->sprite_order[i];
		j = i;
		while (j > 0 && specs->sprite_distance[j - 1] < v)
		{
			specs->sprite_distance[j] = specs->sprite_distance[j - 1];
			specs->sprite_order[j] = specs->sprite_order[j - 1];
			j = j - 1;
		}
		specs->sprite_distance[j] = v;
		specs->sprite_order[j] = z;
		i++;
	}
}

void		draw(t_specs *specs)
{
	int		i;

	draw_wall(specs);
	i = 0;
	while (i < specs->num_prites)
	{
		specs->sprite_order[i] = i;
		specs->sprite_distance[i] = ((specs->pos.x - specs->sprites[i].x)
		* (specs->pos.x - specs->sprites[i].x)
		+ (specs->pos.y - specs->sprites[i].y)
		* (specs->pos.y - specs->sprites[i].y));
		i++;
	}
	sort_sprites(specs);
	draw_sprites(specs);
}

void		render_update(t_specs *specs)
{
	mlx_clear_window(specs->mlx_ptr, specs->mlx_win);
	draw(specs);
	mlx_put_image_to_window(specs->mlx_ptr, specs->mlx_win, specs->buff, 0, 0);
}

int			destroy_exit(t_specs *specs)
{
	mlx_destroy_image(specs->mlx_ptr, specs->buff);
	mlx_destroy_window((*specs).mlx_ptr, (*specs).mlx_win);
	exit(0);
}

void		error_exit(char *error)
{
	ft_putstr_fd(error, 1);
	exit(1);
}
