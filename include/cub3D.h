/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/12 12:04:06 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>

// how many radians to turn on one keypress
const static double	g_cam_turn_speed = 0.02;
// how many tiles to walk on one keypress
const static double	g_player_walk_speed = 0.1;

typedef struct s_map_line
{
	char		*line;
	int			length;
	struct s_map_line	*next;
	struct s_map_line	*previous;
}	t_map_line;

typedef struct s_point_double
{
	double	x;
	double	y;
}	t_point_double;

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

typedef struct s_draw
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	int				image_width;
	int				image_heigth;
	t_point_double	player_pos;
	t_point_double	player_dir;
	t_point_double	camera_plane;
} t_draw;

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

//draw_tools.c
void	 draw_vert_line(mlx_image_t *image, int x, int start_y, int end_y, \
						uint32_t color);
void	draw_floor_and_ceiling(mlx_image_t *image, t_draw *data);

//cam_move.c
void	cam_move_fwd(t_draw *data);
void	cam_move_back(t_draw *data);
void	cam_strafe_left(t_draw *data);
void	cam_strafe_right(t_draw *data);
//cam_turn.c
void	cam_turn_left(t_draw *data);
void	cam_turn_right(t_draw *data);
#endif
