/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:45:08 by obounri           #+#    #+#             */
/*   Updated: 2021/03/08 16:41:29 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	init_t_sp(t_specs *specs, t_sp *sp, int i)
{
	sp->sprite.x = specs->sprites[specs->sprite_order[i]].x -
	specs->pos.x + 0.5;
	sp->sprite.y = specs->sprites[specs->sprite_order[i]].y -
	specs->pos.y + 0.5;
	sp->invdet = 1.0 / (specs->plane.x * specs->dir.y - specs->dir.x *
	specs->plane.y);
	sp->transform.x = sp->invdet * (specs->dir.y * sp->sprite.x -
	specs->dir.x * sp->sprite.y);
	sp->transform.y = sp->invdet * (-(specs->plane.y) * sp->sprite.x +
	specs->plane.x * sp->sprite.y);
	sp->spritescreenx = (int)((specs->rx / 2) * (1 + sp->transform.x /
	sp->transform.y));
}

static void	init_start_end(t_specs *specs, t_sp *sp)
{
	sp->sprite_height = fabs((specs->ry / (sp->transform.y))) / V_DIV;
	sp->drawstart.y = -sp->sprite_height / 2 + specs->ry / 2 + sp->transform.y;
	if (sp->drawstart.y < 0)
		sp->drawstart.y = 0;
	sp->drawend.y = sp->sprite_height / 2 + specs->ry / 2 + sp->transform.y;
	if (sp->drawend.y >= specs->ry)
		sp->drawend.y = specs->ry - 1;
	sp->sprite_width = fabs((specs->ry / (sp->transform.y))) / U_DIV;
	sp->drawstart.x = -sp->sprite_width / 2 + sp->spritescreenx;
	if (sp->drawstart.x < 0)
		sp->drawstart.x = 0;
	sp->drawend.x = sp->sprite_width / 2 + sp->spritescreenx;
	if (sp->drawend.x >= specs->rx)
		sp->drawend.x = specs->rx - 1;
}

static void	sprite_to_buffer(t_specs *specs, t_sp *sp, int y)
{
	while (y < sp->drawend.y)
	{
		sp->d = (y - sp->transform.y) * 256 - specs->ry * 128 +
			sp->sprite_height * 128;
		sp->tex.y = ((sp->d * TEX_HEIGHT) / sp->sprite_height) / 256;
		sp->color = specs->textures->text_sp_data[(TEX_WIDTH * sp->tex.y) +
			sp->tex.x];
		if ((sp->color & 0x00FFFFFF) != 0)
			specs->buff_data[sp->stripe + (specs->rx * y)] = sp->color;
		y++;
	}
}

void		draw_sprites(t_specs *specs)
{
	int		i;
	int		y;
	t_sp	sp;

	i = 0;
	while (i < specs->num_prites)
	{
		init_t_sp(specs, &sp, i);
		init_start_end(specs, &sp);
		sp.stripe = sp.drawstart.x;
		while (sp.stripe < sp.drawend.x)
		{
			sp.tex.x = (int)(256 * (sp.stripe - (-sp.sprite_width / 2 +
				sp.spritescreenx)) * TEX_WIDTH / sp.sprite_width) / 256;
			y = sp.drawstart.y;
			if (sp.transform.y > 0 && sp.stripe > 0 && sp.stripe < specs->rx &&
				sp.transform.y < specs->z_buffer[sp.stripe])
				sprite_to_buffer(specs, &sp, y);
			sp.stripe++;
		}
		i++;
	}
}
