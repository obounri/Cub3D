/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:00:18 by obounri           #+#    #+#             */
/*   Updated: 2021/03/08 16:41:29 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		init_position(t_specs *specs)
{
	int a;
	int b;
	int pos;

	pos = 0;
	a = 0;
	while (specs->map[a] != NULL)
	{
		b = 0;
		while (specs->map[a][b] != '\0')
		{
			if (ft_strchr(INIT, specs->map[a][b]) != NULL)
			{
				if (pos > 0)
					error_exit("Error :\nProvide only one init position.\n");
				specs->pos.x = a + 0.5;
				specs->pos.y = b + 0.5;
				init_direction_ns(a, b, specs);
				pos += 1;
			}
			b++;
		}
		a++;
	}
	return (pos == 1);
}

void	init_textures1(t_specs *specs)
{
	if (!(specs->textures->text_sp = mlx_png_file_to_image(specs->mlx_ptr,
	specs->sprite, &specs->textures->w, &specs->textures->h)))
		error_exit("Error :\nmlx_png_file_to_image() failed.\n");
	specs->textures->text_sp_data =
	(int *)mlx_get_data_addr(specs->textures->text_sp, &(specs->textures->bpp),
	&(specs->textures->line_length), &(specs->textures->endian));
	if (!(specs->textures->texte = mlx_png_file_to_image(specs->mlx_ptr,
	specs->ea, &specs->textures->w, &specs->textures->h)))
		error_exit("Error :\nmlx_png_file_to_image() failed.\n");
	specs->textures->texte_data =
	(int *)mlx_get_data_addr(specs->textures->texte, &(specs->textures->bpp),
	&(specs->textures->line_length), &(specs->textures->endian));
}

void	init_textures2(t_specs *specs)
{
	if (!(specs->textures->textn = mlx_png_file_to_image(specs->mlx_ptr,
	specs->no, &specs->textures->w, &specs->textures->h)))
		error_exit("Error :\nmlx_png_file_to_image() failed.\n");
	specs->textures->textn_data =
	(int *)mlx_get_data_addr(specs->textures->textn, &(specs->textures->bpp),
	&(specs->textures->line_length), &(specs->textures->endian));
	if (!(specs->textures->texts = mlx_png_file_to_image(specs->mlx_ptr,
	specs->so, &specs->textures->w, &specs->textures->h)))
		error_exit("Error :\nmlx_png_file_to_image() failed.\n");
	specs->textures->texts_data =
	(int *)mlx_get_data_addr(specs->textures->texts, &(specs->textures->bpp),
	&(specs->textures->line_length), &(specs->textures->endian));
	if (!(specs->textures->textw = mlx_png_file_to_image(specs->mlx_ptr,
	specs->we, &specs->textures->w, &specs->textures->h)))
		error_exit("Error :\nmlx_png_file_to_image() failed.\n");
	specs->textures->textw_data =
	(int *)mlx_get_data_addr(specs->textures->textw, &(specs->textures->bpp),
	&(specs->textures->line_length), &(specs->textures->endian));
}

void	sprites_data(t_specs *specs)
{
	int i;
	int j;
	int s;

	specs->sprites = malloc(specs->num_prites * sizeof(t_spr));
	i = 0;
	s = -1;
	while (specs->map[i])
	{
		j = 0;
		while (specs->map[i][j])
		{
			if (specs->map[i][j] == '2')
			{
				specs->sprites[++s].x = i;
				specs->sprites[s].y = j;
				specs->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	specs->z_buffer = malloc(specs->rx * sizeof(double));
	specs->sprite_order = malloc(specs->num_prites * sizeof(int));
	specs->sprite_distance = malloc(specs->num_prites * sizeof(double));
}

void	init(t_specs *specs)
{
	if (init_position(specs) != 1)
		error_exit("Error :\nProvide init position.\n");
	(*specs).mlx_ptr = mlx_init();
	(*specs).mlx_win =
	mlx_new_window((*specs).mlx_ptr, (*specs).rx, (*specs).ry, "New Window");
	specs->buff = mlx_new_image(specs->mlx_ptr, (*specs).rx, (*specs).ry);
	specs->buff_data = (int *)mlx_get_data_addr(specs->buff,
	&specs->bpp, &specs->line_length, &specs->endian);
	init_textures1(specs);
	init_textures2(specs);
	sprites_data(specs);
	draw(specs);
	if (specs->save == 1)
	{
		buffer_to_bmp(specs);
		destroy_exit(specs);
	}
	mlx_put_image_to_window(specs->mlx_ptr, specs->mlx_win, specs->buff, 0, 0);
}
