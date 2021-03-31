/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 09:05:54 by obounri           #+#    #+#             */
/*   Updated: 2021/03/14 15:13:24 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	path_ok_sprite(t_specs *specs, char **infos)
{
	int y;
	int len;

	y = 0;
	while (infos[y] != NULL)
		y++;
	if (y != 2)
		error_exit("Error :\nProvide paths correctly.\n");
	len = ft_strlen(infos[1]);
	if (!ft_strnstr(&infos[1][len - 4], ".png", 4))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (((open(infos[1], O_RDONLY)) == -1) ||
	((open(infos[1], O_DIRECTORY)) != -1))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (specs->sprite != NULL)
		error_exit("Error:\nDuplicate element?.\n");
	(*specs).sprite = infos[1];
}

void	path_ok_we(t_specs *specs, char **infos)
{
	int y;
	int len;

	y = 0;
	while (infos[y] != NULL)
		y++;
	if (y != 2)
		error_exit("Error :\nProvide paths correctly.\n");
	if (ft_strlen(infos[0]) != 2)
		error_exit("Error :\nProvide paths correctly.\n");
	len = ft_strlen(infos[1]);
	if (!ft_strnstr(&infos[1][len - 4], ".png", 4))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (((open(infos[1], O_RDONLY)) == -1) ||
	((open(infos[1], O_DIRECTORY)) != -1))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (specs->we != NULL)
		error_exit("Error:\nDuplicate element?.\n");
	(*specs).we = infos[1];
}

void	path_ok_ea(t_specs *specs, char **infos)
{
	int y;
	int len;

	y = 0;
	while (infos[y] != NULL)
		y++;
	if (y != 2)
		error_exit("Error :\nProvide paths correctly.\n");
	len = ft_strlen(infos[1]);
	if (!ft_strnstr(&infos[1][len - 4], ".png", 4))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (((open(infos[1], O_RDONLY)) == -1) ||
	((open(infos[1], O_DIRECTORY)) != -1))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (specs->ea != NULL)
		error_exit("Error:\nDuplicate element?.\n");
	(*specs).ea = infos[1];
}

void	path_ok_no(t_specs *specs, char **infos)
{
	int y;
	int len;

	y = 0;
	while (infos[y] != NULL)
		y++;
	if (y != 2)
		error_exit("Error :\nProvide paths correctly.\n");
	len = ft_strlen(infos[1]);
	if (!ft_strnstr(&infos[1][len - 4], ".png", 4))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (((open(infos[1], O_RDONLY)) == -1) ||
	((open(infos[1], O_DIRECTORY)) != -1))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (specs->no != NULL)
		error_exit("Error:\nDuplicate element?.\n");
	(*specs).no = infos[1];
}

void	path_ok_so(t_specs *specs, char **infos)
{
	int y;
	int len;

	y = 0;
	while (infos[y] != NULL)
		y++;
	if (y != 2)
		error_exit("Error :\nProvide paths correctly.\n");
	len = ft_strlen(infos[1]);
	if (!ft_strnstr(&infos[1][len - 4], ".png", 4))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (((open(infos[1], O_RDONLY)) == -1) ||
	((open(infos[1], O_DIRECTORY)) != -1))
		error_exit("Error :\nOne of the paths provided is invalid.\n");
	if (specs->so != NULL)
		error_exit("Error:\nDuplicate element?.\n");
	(*specs).so = infos[1];
}
