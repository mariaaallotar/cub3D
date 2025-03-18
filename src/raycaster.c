/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:36:45 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/18 14:48:10 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

typedef struct s_rcast
{
	t_point_double	ray_dir;
	t_point_double	ray_step_dist;
	t_point_int		ray_pos;
	t_point_double	ray_dist_to_side;
	t_point_int		step_dir;
	int				wall_side;
	double			perp_wall_dist;
	int				wall_heigth;
	int				start_draw;
	int				end_draw;
	double			wall_x;
	int				tex_x;
	double			tex_y_step;
	double			tex_pos;
}	t_rcast;

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
// sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x))
// is simplified to
// ray_step_dist.x = fabs(1/ray_dir.x)
static t_point_double	calc_ray_step_distance(t_point_double ray_dir)
{
	t_point_double	ray_step_dist;

	if (ray_dir.x == 0)
		ray_step_dist.x = 1e30;
	else
		ray_step_dist.x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		ray_step_dist.y = 1e30;
	else
		ray_step_dist.y = fabs(1 / ray_dir.y);
	return (ray_step_dist);
}

// are we moving is positive or negative direction on the axis?
static t_point_int	calc_ray_step_direction(t_point_double ray_dir)
{
	t_point_int		step_dir;

	if (ray_dir.x < 0)
		step_dir.x = -1;
	else
		step_dir.x = 1;
	if (ray_dir.y < 0)
		step_dir.y = -1;
	else
		step_dir.y = 1;
	return (step_dir);
}

// distance to first tile side we encounter
static t_point_double	calc_ray_dist_to_side(t_draw *data, t_rcast *rcast)
{
	t_point_double	ray_dist_to_side;

	if (rcast->ray_dir.x < 0)
	{
		ray_dist_to_side.x = (data->player_pos.x - rcast->ray_pos.x)
			* rcast->ray_step_dist.x;
	}
	else
	{
		ray_dist_to_side.x = (rcast->ray_pos.x + 1.0 - data->player_pos.x)
			* rcast->ray_step_dist.x;
	}
	if (rcast->ray_dir.y < 0)
	{
		ray_dist_to_side.y = (data->player_pos.y - rcast->ray_pos.y)
			* rcast->ray_step_dist.y;
	}
	else
	{
		ray_dist_to_side.y = (rcast->ray_pos.y + 1.0 - data->player_pos.y)
			* rcast->ray_step_dist.y;
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

// This is the core of the DDA algo, it returns the side of the wall
// that has been hit and also increments ray_dist_to_side for later. 
// Cannot enter infinite loop because ray_pos is incremented on every loop. 
// There is no failure when the ray goes out of bounds, we just pretend 
// there is a wall and keep chugging (is this a good idea?)
static int	cast_ray(t_rcast *rcast, char **map)
{
	int	wall_side;

	wall_side = 0;
	while (true)
	{
		if (rcast->ray_dist_to_side.x < rcast->ray_dist_to_side.y)
		{
			rcast->ray_dist_to_side.x += rcast->ray_step_dist.x;
			rcast->ray_pos.x += rcast->step_dir.x;
			wall_side = 0;
		}
		else
		{
			rcast->ray_dist_to_side.y += rcast->ray_step_dist.y;
			rcast->ray_pos.y += rcast->step_dir.y;
			wall_side = 1;
		}
		if (out_of_bounds(rcast->ray_pos, map))
			return (wall_side);
		if (map[rcast->ray_pos.y][rcast->ray_pos.x] == '1')
			return (wall_side);
	}
}

// calculate distance of wall to camera plane, not to player. This
// avoids fish-eye effect
static double	calc_perp_wall_dist(t_rcast *rcast)
{
	if (rcast->wall_side == 0)
		return (rcast->ray_dist_to_side.x - rcast->ray_step_dist.x);
	else
		return (rcast->ray_dist_to_side.y - rcast->ray_step_dist.y);
}

// normally should never go to the last return
static	mlx_texture_t	*pick_texture(t_cub3D *main_struct, int wall_side,
										t_point_int step_dir)
{
	if (wall_side == 0 && step_dir.x < 0)
		return (main_struct->input.ea_texture);
	if (wall_side == 0 && step_dir.x > 0)
		return (main_struct->input.we_texture);
	if (wall_side == 1 && step_dir.y < 0)
		return (main_struct->input.so_texture);
	if (wall_side == 1 && step_dir.y > 0)
		return (main_struct->input.no_texture);
	return (main_struct->input.ea_texture);
}

static void	calc_wall_heigth(t_draw *draw, t_rcast *rcast)
{
	rcast->wall_heigth = draw->image_heigth / rcast->perp_wall_dist;
	rcast->start_draw = -rcast->wall_heigth / 2 + draw->image_heigth / 2;
	if (rcast->start_draw < 0)
		rcast->start_draw = 0;
	rcast->end_draw = rcast->wall_heigth / 2 + draw->image_heigth / 2;
	if (rcast->end_draw > draw->image_heigth)
		rcast->end_draw = draw->image_heigth -1;
}

static void	calc_wall_x(t_rcast *rcast, t_draw *draw)
{
	if (rcast->wall_side == 0)
	{
		rcast->wall_x = draw->player_pos.y + rcast->perp_wall_dist
			* rcast->ray_dir.y;
	}
	else
	{
		rcast->wall_x = draw->player_pos.x + rcast->perp_wall_dist
			* rcast->ray_dir.x;
	}
	rcast->wall_x -= floor(rcast->wall_x);
}

// the if-statement here mirrors some of the textures in some situations
static void	find_pos_in_texture(mlx_texture_t *texture,
								t_rcast *rcast, t_draw *draw)
{
	rcast->tex_x = rcast->wall_x * (double) texture->width;
	if ((rcast->wall_side == 0 && rcast->ray_dir.x < 0)
		|| (rcast->wall_side == 1 && rcast->ray_dir.y > 0))
	{
		rcast->tex_x = texture->width - rcast->tex_x - 1;
	}
	rcast->tex_y_step = (double) texture->height / rcast->wall_heigth;
	rcast->tex_pos = (rcast->start_draw - draw->image_heigth
			/ 2.0 + rcast->wall_heigth / 2.0) * rcast->tex_y_step;
}

// the *4 +1 +2 and +3 is due to how data is stored in mlx_texture_t
// it is actually an array of 4* the number of pixels in the image
// where each number represents one color channel of one pixel
static unsigned int	get_color_from_texture(mlx_texture_t *texture, int tex_x,
											int tex_y)
{
	return (convert_color(
			texture->pixels[(texture->width * tex_y + tex_x) * 4],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 1],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 2],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 3]
		));
}

static void	draw_with_texture(mlx_texture_t *texture, t_rcast *rcast,
								t_draw *draw, int cur_screen_col)
{
	int				i;
	unsigned int	tex_y;
	unsigned int	color;

	i = rcast->start_draw;
	while (i < rcast->end_draw)
	{
		tex_y = rcast->tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		rcast->tex_pos += rcast->tex_y_step;
		color = get_color_from_texture(texture, rcast->tex_x, tex_y);
		mlx_put_pixel(draw->image, cur_screen_col, i, color);
		i++;
	}
}

static void	draw_wall_column_tex(t_cub3D *main_struct, t_rcast *rcast,
									int cur_screen_col)
{
	t_draw			*draw;
	mlx_texture_t	*texture;

	draw = &main_struct->draw;
	calc_wall_heigth(&main_struct->draw, rcast);
	calc_wall_x(rcast, &main_struct->draw);
	texture = pick_texture(main_struct, rcast->wall_side, rcast->step_dir);
	find_pos_in_texture(texture, rcast, draw);
	draw_with_texture(texture, rcast, draw, cur_screen_col);
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

void	draw(t_draw *data, t_cub3D *main_struct)
{
	t_rcast	rcast;
	int		cur_screen_col;

	draw_floor_and_ceiling(main_struct);
	data->camera_plane = calc_camera_plane(data->player_dir);
	cur_screen_col = 0;
	while (cur_screen_col < data->image_width)
	{
		rcast.ray_pos.x = (int) data->player_pos.x;
		rcast.ray_pos.y = (int) data->player_pos.y;
		rcast.ray_dir = calc_ray_direction(data, cur_screen_col);
		rcast.ray_step_dist = calc_ray_step_distance(rcast.ray_dir);
		rcast.step_dir = calc_ray_step_direction(rcast.ray_dir);
		rcast.ray_dist_to_side = calc_ray_dist_to_side(data, &rcast);
		rcast.wall_side = cast_ray(&rcast, main_struct->input.map);
		rcast.perp_wall_dist = calc_perp_wall_dist(&rcast);
		draw_wall_column_tex(main_struct, &rcast, cur_screen_col);
		cur_screen_col++;
	}
}
