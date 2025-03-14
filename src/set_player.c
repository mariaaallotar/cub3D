/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:32:22 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/14 11:33:54 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_player_direction(char direction, t_cub3D *main_struct)
{
	int	x;
	int	y;

	if (direction == 'N')
	{
		x = 0;
		y = -1;
	}
	else if (direction == 'E')
	{
		x = 1;
		y = 0;
	}
	else if (direction == 'S')
	{
		x = 0;
		y = 1;
	}
	else
	{
		x = -1;
		y = 0;
	}
	main_struct->draw.player_dir.x = x;
	main_struct->draw.player_dir.y = y;
}

void	set_player(t_map_line *current, t_cub3D *main_struct, int i,
	char direction)
{
	main_struct->draw.player_pos.x = i;
	i = 0;
	while (current->previous != NULL)
	{
		i++;
		current = current->previous;
	}
	main_struct->draw.player_pos.y = i;
	set_player_direction(direction, main_struct);
}
