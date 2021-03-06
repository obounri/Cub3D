/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:38:49 by obounri           #+#    #+#             */
/*   Updated: 2021/01/16 19:07:54 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		*ft_memccpy(void *dst, const void *src, int c, int n)
{
	unsigned char	*src1;
	unsigned char	*dst1;
	int				i;

	src1 = (unsigned char*)src;
	dst1 = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		dst1[i] = src1[i];
		if (src1[i] == (unsigned char)c)
			dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}

int			ft_strlcpy(char *dst, const char *src, int c)
{
	int i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i < (int)c - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (c > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char		*join_char(char **line, const char *cache, int *i)
{
	char	*str;
	int		n;
	int		len;

	n = 0;
	len = ft_strlen(*line) + ft_strlen(cache) + 1;
	if (!(str = (char *)malloc(len * sizeof(char))))
		return (NULL);
	if (*line)
	{
		while ((*line)[n])
		{
			str[n] = (*line)[n];
			n++;
		}
		while (cache[*i] && cache[*i] != '\n')
		{
			str[n] = cache[*i];
			n++;
			*i = *i + 1;
		}
	}
	str[n] = '\0';
	free(*line);
	return (str);
}
