/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:36:45 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/18 15:55:37 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
