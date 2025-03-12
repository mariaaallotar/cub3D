/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/12 14:00:48 by maheleni         ###   ########.fr       */
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
	NOT_IDENTIFIER,
	MAP_NOT_LAST,
	INFO_MISSING,
	IDENTIFIER_WITHOUT_VALUE,
	MULT_PLAYER,
	WRONG_CHAR,
	WALL_ERROR,
	NO_PLAYER,
	NEWLINE_IN_MAP,
	PLAYER_OUTSIDE
};

enum e_location
{
	FLOOR,
	CEILING
};

typedef struct s_surrounding_chars
{
	char	left;
	char	right;
	char	up;
	char	down;
}	t_chars;

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
	int				identifier_counter;
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	char    		**map;
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

//memory.c
void	free_everything(t_cub3D	*main_struct, t_map_line **map);
void	free_map_list(t_map_line **map);

//error.c
void	error_and_exit(int return_value);

//color_parsing.c
int	set_floor_ceiling(char *type_identifier, char *color_code,
	t_cub3D *main_struct);

//texture_parsing.c
int	set_wall_texture(char *type_identifier, char *texture,
	t_cub3D *main_struct);

//map_parsing.c
int	start_of_map(char **line, t_cub3D *main_struct);
int	set_map(char *line, int fd, t_map_line **map);

//map_validation.c
int	validate_map(t_map_line **map);
int	check_forbidden_chars(t_map_line *current, int *player_found);


#endif
