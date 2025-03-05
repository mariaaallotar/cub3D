# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 11:56:58 by lemercie          #+#    #+#              #
#    Updated: 2025/03/05 14:30:48 by maheleni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= ./src/
OBJDIR	:= ./obj/

SRCS	:= $(addprefix $(SRCDIR), main.c validate_args.c)
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

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

clean:
	#rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT)
	rm -fr $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBMLX)		#maybe remove
	rm -rf .libmlx_cloned	#maybe remove
	make fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
