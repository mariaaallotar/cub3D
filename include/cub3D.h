/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/06 12:12:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>

typedef struct s_rbg 
{
    unsigned int r;
    unsigned int g;
    unsigned int b; 
}   t_rgb;


typedef struct s_input
{
    t_rgb   floor_color;
    t_rgb   ceiling_color;
    char    *no_texture;
    char    *ea_texture;
    char    *so_texture;
    char    *we_texture;
    //char    **map;
}   t_input;

typedef struct s_cub3D
{
    t_input input;
}   t_cub3D;

//validate_args.c
void	validate_arguments(int argc, char **argv);

//parse_file.c
void    parse_file(int fd, t_cub3D *main_struct);


#endif
