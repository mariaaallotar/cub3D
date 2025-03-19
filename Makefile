# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 11:56:58 by lemercie          #+#    #+#              #
#    Updated: 2025/03/18 16:01:12 by lemercie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -g
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= ./src/
OBJDIR	:= ./obj/

SRCS	:= $(addprefix $(SRCDIR), main.c validate_args.c parse_file.c error.c \
		   memory.c colors.c color_parsing.c texture_parsing.c map_parsing.c \
		   map_validation.c game_loop.c draw_tools.c cam_move.c cam_turn.c \
		   raycaster.c parse_line.c set_player.c map_validation_utils.c \
		   textured_wall.c raycaster_calcs.c pick_texture.c)
OBJS	:= ${SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o}

all: libft libmlx $(NAME)

# --depth 1 avoids downloading whole repo history
.libmlx_cloned:
	git clone --depth 1 --branch v2.4.1 --single-branch \
		https://github.com/codam-coding-college/MLX42.git $(LIBMLX)
	touch .libmlx_cloned

libmlx: .libmlx_cloned
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft: 
	make -C $(LIBFT)

$(NAME): $(OBJS) ./include/cub3D.h
	$(CC) $(OBJS) $(LIBS) $(LIBFT)/libft.a $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c ./include/cub3D.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT)
	rm -fr $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBMLX)
	rm -rf .libmlx_cloned
	make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
