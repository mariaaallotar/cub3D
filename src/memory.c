/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:24 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/19 14:29:21 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	free_2d_array(t_cub3D *main_struct)
{
	char	**map;
	int		i;

	i = 0;
	map = main_struct->input.map;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map_list(t_map_line **map)
{
	t_map_line	*current;
	t_map_line	*next;

	current = *map;
	while (current != NULL)
	{
		free(current->line);
		if (current->next == NULL)
		{
			free(current);
			break ;
		}
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_map_nodes(t_map_line **map)
{
	t_map_line	*current;
	t_map_line	*next;

	current = *map;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	empty_gnl_buffer(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	free_everything(t_cub3D	*main_struct, t_map_line **map)
{
	if (main_struct->input.no_texture != NULL)
		mlx_delete_texture(main_struct->input.no_texture);
	if (main_struct->input.ea_texture != NULL)
		mlx_delete_texture(main_struct->input.ea_texture);
	if (main_struct->input.so_texture != NULL)
		mlx_delete_texture(main_struct->input.so_texture);
	if (main_struct->input.we_texture != NULL)
		mlx_delete_texture(main_struct->input.we_texture);
	if (map != NULL && *map != NULL)
		free_map_list(map);
	if (main_struct->input.map != NULL)
		free_2d_array(main_struct);
}
