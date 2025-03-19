/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:58:27 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/19 13:54:19 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool	pos_walkable(t_cub3D *main_struct, t_point_double new_pos)
{
	char	**map;
	int		new_pos_y;
	int		new_pos_x;

	map = main_struct->input.map;
	new_pos_y = new_pos.y;
	new_pos_x = new_pos.x;
	if (new_pos_y < 0 || new_pos_x < 0)
		return (false);
	if (map[new_pos_y] == NULL)
		return (false);
	if (map[new_pos_y][new_pos_x] == ' ')
		return (false);
	if (map[new_pos_y][new_pos_x] == '\0')
		return (false);
	if (map[new_pos_y][new_pos_x] == '\n')
		return (false);
	if (main_struct->input.map[new_pos_y][new_pos_x] == '1')
		return (false);
	return (true);
}

void	cam_move_fwd(t_cub3D *main_struct)
{
	t_point_double	new_pos;
	t_draw	*data;

	data = &main_struct->draw;
	new_pos.y = data->player_pos.y + data->player_dir.y * g_player_walk_speed;
	new_pos.x = data->player_pos.x + data->player_dir.x * g_player_walk_speed;
	if (pos_walkable(main_struct, new_pos))
	{
		data->player_pos = new_pos;
	}
}

void	cam_move_back(t_cub3D *main_struct)
{
	t_point_double	new_pos;
	t_draw	*data;

	data = &main_struct->draw;
	new_pos.y = data->player_pos.y - data->player_dir.y * g_player_walk_speed;
	new_pos.x = data->player_pos.x - data->player_dir.x * g_player_walk_speed;
	if (pos_walkable(main_struct, new_pos))
	{
		data->player_pos = new_pos;
	}
}

// similar to rotating a vector 90 degrees, we move the player along a vector
// that is at 90 degrees to the current player direction
void	cam_strafe_left(t_cub3D *main_struct)
{
	t_point_double	new_pos;
	t_draw	*data;

	data = &main_struct->draw;
	new_pos.y = data->player_pos.y - data->player_dir.x * g_player_walk_speed;
	new_pos.x = data->player_pos.x + data->player_dir.y * g_player_walk_speed;
	if (pos_walkable(main_struct, new_pos))
	{
		data->player_pos = new_pos;
	}
}

void	cam_strafe_right(t_cub3D *main_struct)
{
	t_point_double	new_pos;
	t_draw	*data;

	data = &main_struct->draw;
	new_pos.y = data->player_pos.y + data->player_dir.x * g_player_walk_speed;
	new_pos.x = data->player_pos.x - data->player_dir.y * g_player_walk_speed;
	if (pos_walkable(main_struct, new_pos))
	{
		data->player_pos = new_pos;
	}
}
