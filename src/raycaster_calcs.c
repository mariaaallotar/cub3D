/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_calcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:52:54 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/19 13:59:39 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_point_double	calc_ray_direction(t_draw *data, int cur_screen_col)
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
t_point_double	calc_ray_step_distance(t_point_double ray_dir)
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
t_point_int	calc_ray_step_direction(t_point_double ray_dir)
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
t_point_double	calc_ray_dist_to_side(t_draw *data, t_rcast *rcast)
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

bool	out_of_bounds(t_point_int ray_pos, char **map)
{
	if (ray_pos.y < 0 || ray_pos.x < 0)
		return (true);
	if (map[ray_pos.y] == NULL)
		return (true);
	if (map[ray_pos.y][ray_pos.x] == ' ')
		return (true);
	if (map[ray_pos.y][ray_pos.x] == '\0')
		return (true);
	if (map[ray_pos.y][ray_pos.x] == '\n')
		return (true);
	return (false);
}
