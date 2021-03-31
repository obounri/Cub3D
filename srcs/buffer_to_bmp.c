/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_to_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:59:28 by obounri           #+#    #+#             */
/*   Updated: 2021/03/08 11:01:20 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void		set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

void		ft_header(t_specs *specs, t_bmp *bmp)
{
	int		i;

	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[10] = 54;
	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[12] = 1;
	bmp->info[14] = 24;
	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
	set_header(&bmp->header[2], bmp->size);
	set_header(&bmp->info[4], specs->rx);
	set_header(&bmp->info[8], specs->ry);
	write(bmp->fd, bmp->header, 14);
	write(bmp->fd, bmp->info, 40);
}

void		imgbmp(t_specs *specs, t_bmp *bmp)
{
	int		i;
	int		j;
	int		x;
	int		y;

	j = -1;
	while (++j < specs->ry)
	{
		i = -1;
		while (++i < specs->rx)
		{
			x = i;
			y = specs->ry - 1 - j;
			bmp->color = specs->buff_data[x + y * specs->rx];
			write(bmp->fd, &bmp->color, 3);
		}
		i = -1;
		while (++i < (4 - (specs->rx * 3) % 4) % 4)
			write(bmp->fd, &bmp->pad, 1);
	}
}

void		buffer_to_bmp(t_specs *specs)
{
	t_bmp	bmp;
	int		imgsize;

	imgsize = 3 * specs->rx * specs->ry;
	bmp.size = 54 + imgsize;
	bmp.img = ft_calloc(imgsize, sizeof(char));
	bmp.fd = open("img.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	ft_header(specs, &bmp);
	imgbmp(specs, &bmp);
	free(bmp.img);
	close(bmp.fd);
}
