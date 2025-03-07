/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/12 11:19:20 by lemercie         ###   ########.fr       */
/*   Updated: 2025/03/07 15:35:31 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>

typedef struct s_map_line
{
	char		*line;
	int			length;
	struct s_map_line	*next;
	struct s_map_line	*previous;
}	t_map_line;

typedef struct s_rbg 
{
	unsigned int r;
	unsigned int g;
	unsigned int b; 
}	t_rgb;

typedef struct s_input
{
	t_rgb   floor_color;
	t_rgb   ceiling_color;
	char    *no_texture;
	char    *ea_texture;
	char    *so_texture;
	char    *we_texture;
	t_map_line	*map;
	//char    **map;
}	t_input;

typedef struct s_cub3D
{
	t_input input;
}	t_cub3D;

//validate_args.c
void	validate_arguments(int argc, char **argv);

//parse_file.c
void    parse_file(int fd, t_cub3D *main_struct);

//colors.c
int32_t convert_color(int32_t r, int32_t g, int32_t b, int32_t a);
//game_loop.c
void	start_graphics(int image_width, int image_heigth);


#endif
