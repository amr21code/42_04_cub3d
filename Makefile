# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 15:14:15 by anruland          #+#    #+#              #
#    Updated: 2022/07/10 17:42:34 by anruland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -ggdb3

LLIBS	=	-L./libft/ -lft -lm -lmlx -lX11 -lXext
MLIBS	=	-L./libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit

OS		= $(shell uname)

SRC		=	main.c \
			c3d_init.c \
			c3d_error_checks.c \
			c3d_error_checks_helper.c \
			c3d_error_checks_helper2.c \
			c3d_error_checks_map_helper.c \
			c3d_destructor.c \
			c3d_init_config.c \
			c3d_init_map.c \
			c3d_init_textures.c \
			c3d_draw_bg.c \
			c3d_draw_minimap.c \
			c3d_math.c \
			c3d_raycast.c \
			c3d_draw.c \
			c3d_input.c \
			c3d_move.c


# Mac or Linux?
ifeq ($(OS), Linux)
	LIBS = $(LLIBS)
#	SRC = $(LSRC)
endif
ifeq ($(OS), Darwin)
	LIBS = $(MLIBS)
#	SRC = $(MSRC)
endif

all: $(NAME)

$(NAME): setup
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(NAME)

setup:
	make -C libft

clean:
	rm -f ./*.o
	make clean -C libft

fclean: clean
	rm -f ./$(NAME)
	make fclean -C libft

re:	fclean all

.PHONY: setup $(NAME)
