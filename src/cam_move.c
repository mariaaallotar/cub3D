/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:58:27 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/12 13:14:40 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	cam_move_fwd(t_draw *data)
{
	data->player_pos.y += data->player_dir.y * g_player_walk_speed;
	data->player_pos.x += data->player_dir.x * g_player_walk_speed;
}

void	cam_move_back(t_draw *data)
{
	data->player_pos.y -= data->player_dir.y * g_player_walk_speed;
	data->player_pos.x -= data->player_dir.x * g_player_walk_speed;
}

void	cam_strafe_left(t_draw *data)
{
	(void) data;
	// data->camera_plane.y += data->camera_plane.y * 0.1;
	// data->camera_plane.x += data->camera_plane.x * 0.1;
}

void	cam_strafe_right(t_draw *data)
{
	(void) data;
	// data->camera_plane.y -= data->camera_plane.y * 0.1;
	// data->camera_plane.x -= data->camera_plane.x * 0.1;
}
