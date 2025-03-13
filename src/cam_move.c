/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:58:27 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/13 16:46:55 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// TODO:
// calculate new position
// check if new position is in a wall tile
// apply new position
//
bool	pos_walkable(t_draw *data, t_point_double new_pos)
{
	(void) data;
	if (new_pos.y < 0 || new_pos.x < 0)
		return (false);
	// if in bounds and not wall
	return (true);
}

void	cam_move_fwd(t_draw *data)
{
	t_point_double	new_pos;

	new_pos.y = data->player_pos.y + data->player_dir.y * g_player_walk_speed;
	new_pos.x = data->player_pos.x + data->player_dir.x * g_player_walk_speed;
	if (pos_walkable(data, new_pos))
	{
		data->player_pos = new_pos;
	}
}

void	cam_move_back(t_draw *data)
{
	data->player_pos.y -= data->player_dir.y * g_player_walk_speed;
	data->player_pos.x -= data->player_dir.x * g_player_walk_speed;
}

// similar to rotating a vector 90 degrees, we move the player along a vector
// that is at 90 degrees to the current player direction
void	cam_strafe_left(t_draw *data)
{
	data->player_pos.y -= data->player_dir.x * g_player_walk_speed;
	data->player_pos.x += data->player_dir.y * g_player_walk_speed;
}

void	cam_strafe_right(t_draw *data)
{
	data->player_pos.y += data->player_dir.x * g_player_walk_speed;
	data->player_pos.x -= data->player_dir.y * g_player_walk_speed;
}
