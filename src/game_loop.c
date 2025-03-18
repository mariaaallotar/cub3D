/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/18 12:26:53 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

typedef struct s_cast
{
	int				cur_screen_col;
	t_point_double	ray_dir;
	t_point_double	ray_step_dist;
	t_point_int		ray_pos;
	t_point_double	ray_dist_to_side;
	t_point_int		step_dir;
	int				wall_side;
	double			perp_wall_dist;

} t_cast;

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
static t_point_double	calc_ray_dist_to_side(t_draw *data, t_cast *cast)
{
	t_point_double	ray_dist_to_side;

	if (cast->ray_dir.x < 0)
	{
		ray_dist_to_side.x = (data->player_pos.x - cast->ray_pos.x)
			* cast->ray_step_dist.x;
	}
	else
	{
		ray_dist_to_side.x = (cast->ray_pos.x + 1.0 - data->player_pos.x)
			* cast->ray_step_dist.x;
	}
	if (cast->ray_dir.y < 0)
	{
		ray_dist_to_side.y = (data->player_pos.y - cast->ray_pos.y)
			* cast->ray_step_dist.y;
	}
	else
	{
		ray_dist_to_side.y = (cast->ray_pos.y + 1.0 - data->player_pos.y)
			* cast->ray_step_dist.y;
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
static	int	cast_ray(t_cast *cast, char **map)
{
	int	wall_side;

	wall_side = 0;
	while (true)
	{
		if (cast->ray_dist_to_side.x < cast->ray_dist_to_side.y)
		{
			cast->ray_dist_to_side.x += cast->ray_step_dist.x;
			cast->ray_pos.x += cast->step_dir.x;
			wall_side = 0;
		}
		else
		{
			cast->ray_dist_to_side.y += cast->ray_step_dist.y;
			cast->ray_pos.y += cast->step_dir.y;
			wall_side = 1;
		}
		if (out_of_bounds(cast->ray_pos, map))
		{
			// dont fail, just keep chugging (is this a good idea?)
			return (wall_side);
		}
		if (map[cast->ray_pos.y][cast->ray_pos.x] == '1')
		{
			return (wall_side);
		}
	}
}

// calculate distance of wall to camera plane, not to player. This
// avoids fish-eye effect
static double	calc_perp_wall_dist(t_cast *cast)
{
	if (cast->wall_side == 0)
	{
		return (cast->ray_dist_to_side.x - cast->ray_step_dist.x);
	}
	else
	{
		return (cast->ray_dist_to_side.y - cast->ray_step_dist.y);
	}
}

// should never go to the last return
static	mlx_texture_t	*pick_texture(t_cub3D *main_struct, int wall_side, 
								   t_point_int step_dir)
{
	if (wall_side == 0)
	{
		if (step_dir.x < 0)
			return (main_struct->input.ea_texture);
		if (step_dir.x > 0)
			return (main_struct->input.we_texture);
	}
	if (wall_side == 1)
	{
		if (step_dir.y < 0)
			return (main_struct->input.so_texture);
		if (step_dir.y > 0)
			return (main_struct->input.no_texture);
	}
	return (main_struct->input.ea_texture);
}

static void	draw_wall_column_tex(t_cub3D *main_struct, t_cast *cast)
{
	int	wall_heigth;
	int	start_draw;
	int	end_draw;
	int	color;
	t_draw	*draw;
	mlx_texture_t	*texture;

	draw = &main_struct->draw;
	wall_heigth = draw->image_heigth / cast->perp_wall_dist;
	start_draw = -wall_heigth / 2 + draw->image_heigth / 2;
	if (start_draw < 0)
		start_draw = 0;
	end_draw = wall_heigth / 2 + draw->image_heigth /2;
	if (end_draw > draw->image_heigth)
		end_draw = draw->image_heigth -1;

	double	wall_x;
	if (cast->wall_side == 0)
	{
		wall_x = draw->player_pos.y + cast->perp_wall_dist * cast->ray_dir.y;
	}
	else
	{
		wall_x = draw->player_pos.x + cast->perp_wall_dist * cast->ray_dir.x;
	}
	wall_x -= floor(wall_x);

	texture = pick_texture(main_struct, cast->wall_side, cast->step_dir);
	int	tex_x;
	tex_x = (int) (wall_x * (double) texture->width);
//	printf("tex_x: %i\n", tex_x);
	
	//tex_x = texture->width - tex_x - 1;
	//	this block affect mirrored textures
	/* if (wall_side == 0 && ray_dir.x > 0)
	{
		tex_x = texture->width - tex_x - 1;
	}
	else if (wall_side == 1 && ray_dir.y < 0)
	{
		tex_x = texture->width - tex_x - 1;
	} */

	double	tex_y_step = 1;
	tex_y_step = 1.0 * texture->height / wall_heigth;
	double	tex_pos = (start_draw - draw->image_heigth / 2.0 + wall_heigth / 2.0) * tex_y_step;
	int	i;
	i = start_draw;
	while (i < end_draw)
	{
		unsigned int	tex_y;
		// tex_y = (int) tex_pos & (texture->height - 1);
		tex_y = tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += tex_y_step;
		// printf("y: %i, x: %i\n", tex_y, tex_x);
		// tex_x = 0;
	/* 	printf("%i, %i, %i, %i\n",
			main_struct->input.ea_texture->pixels[((texture->width * tex_y + tex_x) * 4) + 0],
			main_struct->input.ea_texture->pixels[((texture->width * tex_y + tex_x) * 4) + 1],
			main_struct->input.ea_texture->pixels[((texture->width * tex_y + tex_x) * 4) + 2],
			main_struct->input.ea_texture->pixels[((texture->width * tex_y + tex_x) * 4) + 3]
		 ); */
		color = convert_color(
			texture->pixels[(texture->width * tex_y + tex_x) * 4],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 1],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 2],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 3]
		);
		mlx_put_pixel(draw->image, cast->cur_screen_col, i, color);
		i++;
	}
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

static void	draw(t_draw *data, t_cub3D *main_struct)
{
	t_cast	cast;

	draw_floor_and_ceiling(main_struct);
	cast.cur_screen_col = 0;
	data->camera_plane = calc_camera_plane(data->player_dir);
	while (cast.cur_screen_col < data->image_width)
	{
		cast.ray_pos.x = (int) data->player_pos.x;
		cast.ray_pos.y = (int) data->player_pos.y;
		cast.ray_dir = calc_ray_direction(data, cast.cur_screen_col);
		cast.ray_step_dist = calc_ray_step_distance(cast.ray_dir);
		cast.step_dir = calc_ray_step_direction(cast.ray_dir);
		cast.ray_dist_to_side = calc_ray_dist_to_side(data, &cast);
		cast.wall_side = cast_ray(&cast, main_struct->input.map);
		cast.perp_wall_dist = calc_perp_wall_dist(&cast);
		draw_wall_column_tex(main_struct, &cast);
		cast.cur_screen_col++;
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
	draw(data, main_struct);
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
