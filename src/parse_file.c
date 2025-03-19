/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:00:53 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/19 11:14:07 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	count_rows(t_map_line *map)
{
	int	rows;

	rows = 0;
	while (map)
	{
		rows++;
		map = map->next;
	}
	return (rows);
}

int	map_to_array(t_cub3D *main_struct, t_map_line *map)
{
	int	rows;
	int	i;

	rows = count_rows(map);
	main_struct->input.map = malloc((rows + 1) * sizeof(char *));
	if (main_struct->input.map == NULL)
	{
		print_error_message(-1);
		free_everything(main_struct, &map);
		exit(1);
	}
	i = 0;
	while (map)
	{
		main_struct->input.map[i] = map->line;
		map = map->next;
		i++;
	}
	main_struct->input.map[i] = NULL;
	return (1);
}

void	check_all_info_present(t_cub3D *main_struct, t_map_line **map)
{
	if (main_struct->input.identifier_counter != 6 || *map == NULL)
	{
		free_everything(main_struct, map);
		print_error_message(INFO_MISSING);
		exit(1);
	}
}

void	read_file(int fd, t_map_line **map, t_cub3D *main_struct)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n' || *(skip_whitespace(line)) == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (start_of_map(&line, fd, main_struct))
		{
			if (parse_map(&line, fd, map, main_struct) < 0)
			{
				free_everything(main_struct, map);
				empty_gnl_buffer(fd);
				exit(1);
			}
			return ;
		}
		parse_line(&line, fd, map, main_struct);
		line = get_next_line(fd);
	}
}

void	parse_input(int fd, t_cub3D *main_struct)
{
	t_map_line	*map;

	map = NULL;
	read_file(fd, &map, main_struct);
	close(fd);
	check_all_info_present(main_struct, &map);
	map_to_array(main_struct, map);
	free_map_nodes(&map);
}
