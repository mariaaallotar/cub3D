/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/14 11:12:40 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static t_point_double	calc_ray_direction(t_draw *data, int cur_screen_col)
{
	t_point_double	ray_dir;
	double			camera_x;

	camera_x = 2 * cur_screen_col / (double) data->image_width - 1;
	ray_dir.x = data->player_dir.x + data->camera_plane.x * camera_x;
	ray_dir.y = data->player_dir.y + data->camera_plane.y * camera_x;
	return (ray_dir);
}

// step distance between tile boundaries
// setting to 1e30 (an arbitrary very large number) avoids division by zero
static t_point_double	calc_ray_step_distance(t_point_double ray_dir)
{
	t_point_double	ray_step_dist;

	if (ray_dir.x == 0)
	{
		ray_step_dist.x = 1e30; 
	}
	else
	{
		// ray_step_dist.x = 
		// sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		ray_step_dist.x = fabs(1/ray_dir.x);
	}
	if (ray_dir.y == 0)
	{
		ray_step_dist.y = 1e30;
	}
	else
	{
		// ray_step_dist.y = 
		// sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
		ray_step_dist.y = fabs(1/ray_dir.y);
	}
	return (ray_step_dist);
}

// are we moving is positive or negative direction on the axis?
static t_point_int	calc_ray_step_direction(t_point_double ray_dir)
{
	t_point_int		step_dir;

	if (ray_dir.x < 0)
	{
		step_dir.x = -1;
	}
	else
	{
		step_dir.x = 1;
	}
	if (ray_dir.y < 0)
	{
		step_dir.y = -1;
	}
	else
	{
		step_dir.y = 1;
	}
	return (step_dir);
}

// distance to first tile side we encounter
static t_point_double	calc_ray_dist_to_side(t_draw *data,
										   t_point_double ray_dir,
										   t_point_int ray_pos,
										   t_point_double ray_step_dist)
{
	t_point_double	ray_dist_to_side;

	if (ray_dir.x < 0)
	{
		ray_dist_to_side.x = (data->player_pos.x - ray_pos.x) * ray_step_dist.x;
	}
	else
	{
		ray_dist_to_side.x = (ray_pos.x + 1.0 - data->player_pos.x)
			* ray_step_dist.x;
	}
	if (ray_dir.y < 0)
	{
		ray_dist_to_side.y = (data->player_pos.y - ray_pos.y) * ray_step_dist.y;
	}
	else
	{
		ray_dist_to_side.y = (ray_pos.y + 1.0 - data->player_pos.y)
			* ray_step_dist.y;
	}
	return (ray_dist_to_side);
}

static bool	out_of_bounds(t_point_int ray_pos, char **map)
{
	if (ray_pos.y < 0 || ray_pos.x < 0)
		return (true);
	if (map[ray_pos.y][ray_pos.x] == ' ')
		return (true);
	if (map[ray_pos.y][ray_pos.x] == '\0')
		return (true);
	if (map[ray_pos.y] == NULL)
		return (true);
	return (false);
}

// This is the core of the DDA algo
// returns the side of the wall that has been hit
// also increments ray_dist_to_side for later
// Cannot enter infinite loop because ray_pos is incremented on every loop
static	int	cast_ray(t_point_double *ray_dist_to_side,
					t_point_double ray_step_dist, t_point_int ray_pos,
					t_point_int step_dir, char **map)
{
	int	wall_side;

	wall_side = 0;
	while (true)
	{
		if (ray_dist_to_side->x < ray_dist_to_side->y)
		{
			ray_dist_to_side->x += ray_step_dist.x;
			ray_pos.x += step_dir.x;
			wall_side = 0;
		}
		else
		{
			ray_dist_to_side->y += ray_step_dist.y;
			ray_pos.y += step_dir.y;
			wall_side = 1;
		}
		if (out_of_bounds(ray_pos, map))
		{
			// dont fail, just keep chugging (is this a good idea?)
			return (wall_side);
		}
		if (map[ray_pos.y][ray_pos.x] == '1')
		{
			return (wall_side);
		}
	}
}

// calculate distance of wall to camera plane, not to player. This
// avoids fish-eye effect
static double	calc_perp_wall_dist(int wall_side,
								 t_point_double ray_dist_to_side,
								 t_point_double ray_step_dist)
{
	if (wall_side == 0)
	{
		return (ray_dist_to_side.x - ray_step_dist.x);
	}
	else
	{
		return (ray_dist_to_side.y - ray_step_dist.y);
	}
}

static void	draw_wall_column(mlx_image_t *image, int cur_screen_col, int wall_side,
							 t_draw *data, double perpendicular_wall_dist)
{
	int	wall_heigth;
	int	start_draw;
	int	end_draw;
	int	color;

	wall_heigth = data->image_heigth / perpendicular_wall_dist;
	start_draw = -wall_heigth / 2 + data->image_heigth / 2;
	if (start_draw < 0)
		start_draw = 0;
	end_draw = wall_heigth / 2 + data->image_heigth /2;
	if (end_draw > data->image_heigth)
		end_draw = data->image_heigth -1;

	if (wall_side == 0)
		color = 0xFF0000FF;
	else
		color = 0x990000FF;
	draw_vert_line(image, cur_screen_col, start_draw, end_draw, color);
}

// camera plane has to be perpendicular to player direction and have a magnitude
// relative to the FOV
static t_point_double	calc_camera_plane(t_point_double player_dir)
{
	t_point_double	camera_plane;
	
	camera_plane.x = -player_dir.y;
	camera_plane.y = player_dir.x;
	camera_plane.x *= g_fov;
	camera_plane.y *= g_fov;
	return (camera_plane);
}

static void	draw(mlx_image_t *image, t_draw *data, t_cub3D *main_struct)
{
	int				cur_screen_col;
	t_point_double	ray_dir;
	t_point_double	ray_step_dist;
	t_point_int		ray_pos;
	t_point_double	ray_dist_to_side;
	t_point_int		step_dir;
	int				wall_side;
	double			perp_wall_dist;

	draw_floor_and_ceiling(image, data);
	cur_screen_col = 0;
	while (cur_screen_col < data->image_width)
	{
		data->camera_plane = calc_camera_plane(data->player_dir);
		ray_pos.x = (int) data->player_pos.x;
		ray_pos.y = (int) data->player_pos.y;
		ray_dir = calc_ray_direction(data, cur_screen_col);
		ray_step_dist = calc_ray_step_distance(ray_dir);
		step_dir = calc_ray_step_direction(ray_dir);
		ray_dist_to_side = calc_ray_dist_to_side(data, ray_dir, ray_pos,
										   ray_step_dist);
		wall_side = cast_ray(&ray_dist_to_side, ray_step_dist, ray_pos, step_dir, main_struct->input.map);
		perp_wall_dist = calc_perp_wall_dist(wall_side, ray_dist_to_side,
												ray_step_dist);
		draw_wall_column(image, cur_screen_col, wall_side, data, perp_wall_dist);
		cur_screen_col++;
	}
}

static void	game_hook(void *param)
{
	t_cub3D		*main_struct;
	t_draw		*data;
	mlx_t		*mlx;
	mlx_image_t	*image;

	main_struct = param;
	data = &(main_struct->draw);
	mlx = data->mlx;
	image = data->image;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		return ;
	}
	draw(image, data, main_struct);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		cam_turn_left(main_struct);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		cam_turn_right(main_struct);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		cam_move_fwd(main_struct);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		cam_move_back(main_struct);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		cam_strafe_left(main_struct);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		cam_strafe_right(main_struct);
	}
}

void	start_graphics(int image_width, int image_heigth, t_cub3D *main_struct)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(image_width, image_heigth, "cub3D", true);
	// if (!mlx)
		// fdf_cleanup_exit(map);
 	image = mlx_new_image(mlx, image_width, image_heigth);
	if (!image)
	{
		mlx_close_window(mlx);
		// fdf_cleanup_exit(map);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		mlx_close_window(mlx);
		// fdf_cleanup_exit(map);
	}
	main_struct->draw.mlx = mlx;
	main_struct->draw.image = image;
	main_struct->draw.image_width = image_width;
	main_struct->draw.image_heigth = image_heigth;
	mlx_loop_hook(mlx, game_hook, main_struct);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
