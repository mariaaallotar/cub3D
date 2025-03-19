/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:29:56 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/19 14:29:42 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	parse_split_line(char **split_line, t_cub3D *main_struct)
{
	if (split_line[0][0] == 'F' || split_line[0][0] == 'C')
	{
		if (set_floor_ceiling(split_line[0], split_line[1], main_struct) < 0)
			return (-1);
		if (split_line[2] != NULL)
			return (print_error_message(EXTRA_VALUE));
		return (1);
	}
	if (set_wall_texture(split_line[0], split_line[1], main_struct) < 0)
		return (-1);
	if (split_line[2] != NULL && split_line[2][0] != '\n')
		return (print_error_message(EXTRA_VALUE));
	return (1);
}

void	parse_line(char **line, int fd, t_map_line **map, t_cub3D *main_struct)
{
	char	**split_line;

	split_line = ft_split(*line, ' ');
	free(*line);
	if (split_line == NULL)
	{
		free_everything(main_struct, map);
		empty_gnl_buffer(fd);
		print_error_message(-1);
		exit(1);
	}
	if (parse_split_line(split_line, main_struct) < 0)
	{
		split_free(split_line, 0);
		free_everything(main_struct, map);
		empty_gnl_buffer(fd);
		exit(1);
	}
	split_free(split_line, 0);
}
