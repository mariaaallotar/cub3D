/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/10 15:21:53 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <errno.h>

enum e_errors
{
	DOUBLE_COLOR_ID = -100,
	DOUBLE_WALL_ID,
	WRONG_RGB_VALUE,
	EXTRA_VALUE,
	NOT_IDENTIFIER
};

typedef struct s_map_line
{
	char		*line;
	int			length;
	struct s_map_line	*next;
	struct s_map_line	*previous;
}	t_map_line;

typedef struct s_rbg 
{
	int r;
	int g;
	int b; 
}	t_rgb;

typedef struct s_input
{
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	t_map_line		*map;
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

//mamory.c
void	free_everything(t_cub3D	*main_struct);

//error.c
void	error_and_exit(int return_value);


#endif
