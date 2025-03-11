/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:00:53 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/11 13:14:15 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	parse_split_line(char **split_line, t_cub3D *main_struct)
{
	int	return_value;

	if (split_line[0][0] == 'F' || split_line[0][0] == 'C')
	{
		return_value = set_floor_ceiling(split_line[0], split_line[1], main_struct);
		if (return_value < 0)
			return (return_value);
		if (split_line[2] != NULL)
			return (EXTRA_VALUE);
		return (1);
	}
	return_value = set_wall_texture(split_line[0], split_line[1], main_struct);
	if (return_value < 0)
		return (return_value);
	if (split_line[2] != NULL)
		return (EXTRA_VALUE);
	return (1);
}

void	parse_file(int fd, t_cub3D *main_struct)
{
	char		*line;
	char		**split_line;
	int			return_value;
	t_map_line	*map;

	map = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n' || *(skip_whitespace(line)) == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (start_of_map(&line, main_struct))
		{
			if (main_struct->input.identifier_counter != 6)
			{
				free(line);
				free_everything(main_struct, &map);
				error_and_exit(MAP_NOT_LAST);
			}
			set_map(line, fd, &map);
			break ;
		}
		split_line = ft_split(line, ' ');
		free(line);
		return_value = parse_split_line(split_line, main_struct);
		if (return_value < 0)
		{
			split_free(split_line, 0);
			free_everything(main_struct, &map);
			error_and_exit(return_value);
		}
		split_free(split_line, 0);
		line = get_next_line(fd);
	}
	close(fd);
	if (main_struct->input.identifier_counter != 6 || map == NULL)
	{
		free_everything(main_struct, &map);
		error_and_exit(INFO_MISSING);
	}
	// return_value = validate_map(&map, main_struct);
	// if (return_value < 0)
	// {
	// 	free_everything(main_struct, &map);
	// 	error_and_exit(return_value);
	// }
	free_map_list(&map);
}
