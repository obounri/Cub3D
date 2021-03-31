# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obounri <obounri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 18:59:12 by obounri           #+#    #+#              #
#    Updated: 2021/03/13 16:09:54 by obounri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = cub3D
LIB = cub3d.a
CFLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -lmlx -framework OpenGl -framework Appkit
LIBFT_SOURCES = srcs/libft/ft_strlen.c \
	srcs/libft/ft_putchar_fd.c \
	srcs/libft/ft_putstr_fd.c \
	srcs/libft/ft_strncmp.c \
	srcs/libft/ft_split.c \
	srcs/libft/ft_strtrim.c \
	srcs/libft/ft_substr.c \
	srcs/libft/ft_atoi.c \
	srcs/libft/ft_strnstr.c \
	srcs/libft/ft_strdup.c \
	srcs/libft/ft_bzero.c \
	srcs/libft/ft_calloc.c \
	srcs/libft/ft_strchr.c \
	srcs/libft/ft_isdigit.c
LIBFT_OBJS = $(LIBFT_SOURCES:.c=.o)
UTILS_SOURCES = srcs/parser.c \
	srcs/init.c \
	srcs/utils.c \
	srcs/utils2.c \
	srcs/gnl/get_next_line.c \
	srcs/gnl/get_next_line_utils.c \
	srcs/parsing_map.c \
	srcs/parsing_errors.c \
	srcs/paths.c \
	srcs/draw_wall.c \
	srcs/draw_sprites.c \
	srcs/buffer_to_bmp.c
UTILS_OBJS = $(UTILS_SOURCES:.c=.o)

all: $(NAME)

$(NAME): main.c $(LIB) srcs/includes/cub3d.h
	$(CC) $(CFLAGS) main.c $(LIB) $(FRAMEWORKS) -lz srcs/mlx/libmlx.a -o $(NAME)

$(LIB): $(OBJS) $(LIBFT_OBJS) $(UTILS_OBJS)
	ar rcs $(LIB) $(OBJS) $(LIBFT_OBJS) $(UTILS_OBJS)


clean:
	rm -rf $(OBJS) $(LIBFT_OBJS) $(UTILS_OBJS)

fclean: clean
	rm -rf $(LIB) $(NAME) img.bmp

re: fclean all
