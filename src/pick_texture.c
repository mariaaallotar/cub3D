/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:00:09 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/18 16:00:37 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// normally should never go to the last return
mlx_texture_t	*pick_texture(t_cub3D *main_struct, int wall_side,
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
