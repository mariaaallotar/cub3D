/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:24 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/10 13:38:10 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_map_list(t_map_line *map)
{
	t_map_line *current;

	current = map;
	while (current != NULL)
	{
		free(current->line);
		if (current->next == NULL)
		{
			free(current);
			break ;
		}
		current = current->next;
		free(current->previous);
	}
}

void	free_everything(t_cub3D	*main_struct)
{
	if (main_struct->input.no_texture != NULL)
		free(main_struct->input.no_texture);
	if (main_struct->input.ea_texture != NULL)
		free(main_struct->input.ea_texture);
	if (main_struct->input.so_texture != NULL)
		free(main_struct->input.so_texture);
	if (main_struct->input.we_texture != NULL)
		free(main_struct->input.we_texture);
	free_map_list(main_struct->input.map);
}