/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:05:39 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/12 13:11:33 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	cam_turn(t_draw *data, double angle)
{
	double new_x;
	double new_y;

	new_x = data->player_dir.x * cos(angle) - data->player_dir.y * sin(angle);
	new_y = data->player_dir.x * sin(angle) + data->player_dir.y * cos(angle);
	data->player_dir.x = new_x;
	data->player_dir.y = new_y;

	new_x = data->camera_plane.x * cos(angle) \
		- data->camera_plane.y * sin(angle);
	new_y = data->camera_plane.x * sin(angle) \
		+ data->camera_plane.y * cos(angle);
	data->camera_plane.x = new_x;
	data->camera_plane.y = new_y;
}

void	cam_turn_left(t_draw *data)
{
	cam_turn(data, -g_cam_turn_speed);
}

void	cam_turn_right(t_draw *data)
{
	cam_turn(data, g_cam_turn_speed);
}
