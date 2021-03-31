/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:38 by obounri           #+#    #+#             */
/*   Updated: 2021/03/14 15:17:17 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	check_if_digit(char **infos)
{
	int y;
	int i;

	i = 0;
	while (infos[i] != NULL)
		i++;
	if (i != 3)
		error_exit("Resolution error.\nEx : R 1200 540.\n");
	i = 1;
	while (infos[i])
	{
		y = 0;
		while (infos[i][y])
		{
			if (!ft_isdigit(infos[i][y]))
				error_exit("Resolution error.\nEx : R 1200 540.\n");
			y++;
		}
		i++;
	}
}

void		r_err(t_specs *specs, char **infos)
{
	int		w;
	int		h;

	if ((specs->rx != 0) && (specs->ry != 0))
		error_exit("Error:\nDuplicate element?.\n");
	check_if_digit(infos);
	w = ft_atoi(infos[1]);
	h = ft_atoi(infos[2]);
	if ((w <= 0) || (h <= 0))
		error_exit("Resolution error.\nEx : R 1200 540.\n");
	if (w > 2880 || h > 1485)
	{
		specs->rx = 2880;
		specs->ry = 1485;
	}
	else
	{
		specs->rx = w;
		specs->ry = h;
	}
}

int			create_rgb(t_specs *specs, char *rgb)
{
	char	**colors;
	int		y;
	int		i;
	int		tmp;

	if ((specs->floor != 0) && (specs->ceiling != 0))
		error_exit("Error:\nDuplicate element?.\n");
	colors = ft_split(rgb, ',');
	y = 0;
	while (colors[y] != NULL)
	{
		i = 0;
		while (colors[y][i])
			if (!ft_isdigit(colors[y][i++]))
				error_exit("Color error.\nEx : F 255,140,0.\n");
		tmp = ft_atoi(colors[y]);
		if ((tmp < 0) || (tmp > 255))
			error_exit("Color error.\nEx : F 255,140,0.\n");
		y++;
	}
	if (y != 3)
		error_exit("Color error.\nEx : F 255,140,0.\n");
	return (ft_atoi(colors[0]) << 16 |
	ft_atoi(colors[1]) << 8 | ft_atoi(colors[2]));
}

static void	check_closed_map(int i, int j, t_specs *specs)
{
	if (i == 0 || j == 0)
		error_exit("Error :\nThe map is not closed.\n");
	if (j + 1 == (int)ft_strlen(specs->map[i]))
		error_exit("Error :\nThe map is not closed.\n");
	if (i + 1 == specs->h_map)
		error_exit("Error :\nThe map is not closed.\n");
	if (specs->map[i - 1][j] == '-' || specs->map[i - 1][j] == '\0' ||
	specs->map[i - 1][j] == ' ')
		error_exit("Error :\nThe map is not closed.\n");
	if (specs->map[i][j + 1] == '-')
		error_exit("Error :\nThe map is not closed.\n");
	if (specs->map[i + 1][j] == '-' || specs->map[i + 1][j] == '\0' ||
	specs->map[i + 1][j] == ' ')
		error_exit("Error :\nThe map is not closed.\n");
	if (specs->map[i][j - 1] == '-')
		error_exit("Error :\nThe map is not closed.\n");
}

void		check_map(t_specs *specs)
{
	int		i;
	int		j;

	i = 0;
	specs->num_prites = 0;
	while (specs->map[i])
	{
		j = 0;
		while (specs->map[i][j])
		{
			if (ft_strchr(MAP_CHARS, specs->map[i][j]) == NULL)
				error_exit("Error :\nWrong character in the map.\n");
			if ((specs->map[i][j] == '0') ||
			(ft_strchr(INIT, specs->map[i][j]) != NULL) ||
			(specs->map[i][j] == '2'))
				check_closed_map(i, j, specs);
			if (specs->map[i][j] == '2')
				specs->num_prites += 1;
			j++;
		}
		i++;
	}
}
