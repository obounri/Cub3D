/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:33 by obounri           #+#    #+#             */
/*   Updated: 2021/03/10 12:42:14 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	file_ok(char *file, int *fd)
{
	int		len;

	len = ft_strlen(file);
	if (!ft_strnstr(&file[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Error :\nFile must be *.cub.\n", 1);
		return (0);
	}
	if (((*fd = open(file, O_RDONLY)) == -1) || (open(file, O_DIRECTORY) != -1))
	{
		ft_putstr_fd("Error :\nCould not find this file, check path.\n", 1);
		return (0);
	}
	return (1);
}

static void	store_spec(char **infos, int *i, t_specs *specs)
{
	char	*id;

	id = infos[0];
	if (!ft_strncmp(id, "R", ft_strlen(id)) && (*i = *i + 1))
		r_err(specs, infos);
	else if (!ft_strncmp(id, "S", ft_strlen(id)) && (*i = *i + 1))
		path_ok_sprite(specs, infos);
	else if (!ft_strncmp(id, "NO", 2) && (*i = *i + 1))
		path_ok_no(specs, infos);
	else if (!ft_strncmp(id, "SO", 2) && (*i = *i + 1))
		path_ok_so(specs, infos);
	else if (!ft_strncmp(id, "WE", 2) && (*i = *i + 1))
		path_ok_we(specs, infos);
	else if (!ft_strncmp(id, "EA", 2) && (*i = *i + 1))
		path_ok_ea(specs, infos);
	else if (!ft_strncmp(id, "F", ft_strlen(id)) && (*i = *i + 1))
		(*specs).floor = create_rgb(specs, infos[1]);
	else if (!ft_strncmp(id, "C", ft_strlen(id)) && (*i = *i + 1))
		(*specs).ceiling = create_rgb(specs, infos[1]);
}

static int	check_id(char *line, int *i, int *start_map, t_specs *specs)
{
	char	**infos;

	infos = ft_split(line, ' ');
	if (*start_map > 0)
		return (-1);
	if (infos[0] == NULL)
	{
		free(line);
		return (0);
	}
	if (infos[0][0] == '1')
	{
		*start_map = *start_map + 1;
		return (-1);
	}
	if (ft_strnstr(IDS, infos[0], 12) != NULL)
	{
		store_spec(infos, i, specs);
		free(line);
	}
	return (1);
}

static void	get_data(int fd, t_specs *specs)
{
	char	*line;
	int		nbr_elements;
	int		len;
	int		start_map;

	start_map = 0;
	nbr_elements = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (check_id(line, &nbr_elements, &start_map, specs) != -1)
			continue;
		if (nbr_elements != 8)
			error_exit("Error:\nMissing elements || Duplicate element.\n");
		if ((len = ft_strlen(line)) > specs->w_map)
			specs->w_map = len;
		specs->h_map++;
		specs->parsed = add_line(line, len, ft_strlen(specs->parsed), specs);
		free(line);
	}
	if (start_map == 0)
		error_exit("Error:\nMissing elements\n");
	specs->h_map++;
	specs->parsed = add_line(line, len, ft_strlen(specs->parsed), specs);
	free(line);
}

void		parser(int ac, char **av, t_specs *specs)
{
	int		fd;

	specs->parsed = NULL;
	specs->w_map = 0;
	specs->h_map = 0;
	specs->rx = 0;
	specs->ry = 0;
	specs->no = NULL;
	specs->so = NULL;
	specs->we = NULL;
	specs->ea = NULL;
	specs->sprite = NULL;
	specs->floor = 0;
	specs->ceiling = 0;
	specs->save = 0;
	if (ac == 3 && !ft_strncmp(av[2], "--save", 10))
		specs->save = 1;
	else if (ac != 2)
		error_exit("Wrong arguments.\n");
	if (file_ok(av[1], &fd) == 1)
		get_data(fd, specs);
	else
		error_exit("Wrong arguments.\n");
}
