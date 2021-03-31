/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:58:44 by obounri           #+#    #+#             */
/*   Updated: 2021/03/09 17:21:24 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	ft_strlen_map(char *line)
{
	int		s;

	if (!line)
		return (0);
	s = 0;
	while ((line[s] == ' ') || (line[s] == '-') || (line[s] == '\t'))
		s++;
	return (ft_strlen(line) - s);
}

static void	new_h_map(t_specs *specs)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (specs->map[i] != NULL)
	{
		if ((ft_strlen_map(specs->map[i]) == 0) &&
			(ft_strlen_map(specs->map[i + 1]) != 0))
			error_exit("Error :\nEmpty line in map.\n");
		else if ((ft_strlen_map(specs->map[i]) == 0) &&
			(ft_strlen_map(specs->map[i + 1]) == 0))
		{
			if (k == 0)
			{
				specs->h_map = i;
				k += 1;
			}
			specs->map[i] = NULL;
		}
		i++;
	}
}

void		init_map(t_specs *specs)
{
	int		i;
	int		j;

	if ((specs->map = malloc((specs->h_map + 1) * sizeof(char *))) == NULL)
		error_exit("Error :\nMemory went oups :(, Retry.");
	i = 0;
	while (i < specs->h_map)
	{
		if ((specs->map[i] = ft_calloc(specs->w_map + 1, sizeof(char))) == NULL)
			error_exit("Error :\nMemory went oups :(, Retry.");
		j = 0;
		while ((*specs->parsed != '/') && (*specs->parsed != '\0'))
		{
			specs->map[i][j] = *specs->parsed++;
			j++;
		}
		i++;
		if (*specs->parsed != '\0')
			specs->parsed++;
		else
			break ;
	}
	specs->map[i] = NULL;
	new_h_map(specs);
	check_map(specs);
}

char		*add_line(char *line, int len_line, int len_map, t_specs *specs)
{
	char	*new_map;
	int		i;

	if ((new_map = malloc((len_map + len_line + 2) * sizeof(char))) == NULL)
		error_exit("Error :\nMemory went oups :(, Retry.");
	i = 0;
	while ((specs->parsed && specs->parsed[i] != '\0'))
	{
		new_map[i] = specs->parsed[i];
		i++;
	}
	(len_map != 0) ? new_map[i++] = '/' : 0;
	while (*line && ((*line == ' ') || (*line == '\t')))
		new_map[i++] = *line++;
	while (*line)
	{
		if ((*line == ' ') || (*line == '\t'))
			new_map[i++] = '-';
		else
			new_map[i++] = *line;
		line++;
	}
	new_map[i] = '\0';
	return (new_map);
}
