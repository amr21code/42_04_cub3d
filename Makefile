# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anruland <anruland@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 15:14:15 by anruland          #+#    #+#              #
#    Updated: 2022/06/20 15:52:25 by anruland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -ggdb3

LLIBS	=	-L./libft/ -lft -lm -lmlx -lX11 -lXext
MLIBS	=	-L./libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit

OS		= $(shell uname)

SRC		=	main.c


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
