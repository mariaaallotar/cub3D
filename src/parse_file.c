/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:00:53 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/13 19:34:55 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	parse_split_line(char **split_line, t_cub3D *main_struct)
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

int	count_rows(t_map_line *map)
{
	int	rows;

	rows= 0;
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

	rows= count_rows(map);
	main_struct->input.map = malloc((rows + 1) * sizeof(char *));
	if (main_struct->input.map == NULL)
		return (-1);
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

void	parse_file(int fd, t_cub3D *main_struct)
{
	char		*line;
	char		**split_line;
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
				close(fd);
				print_error_message(MAP_NOT_LAST);
				exit(1);
			}
			if (set_map(line, fd, &map, main_struct) < 0)
			{
				if (map == NULL)
				{
					free(line);
					free_everything(main_struct, NULL);
					close(fd);
					exit(-1);
				}
				else
				{
					free_everything(main_struct, &map);
					close(fd);
					exit(-1);
				}
			}
			break ;
		}
		split_line = ft_split(line, ' ');
		free(line);
		if (parse_split_line(split_line, main_struct) < 0)
		{
			split_free(split_line, 0);
			free_everything(main_struct, &map);
			close(fd);
			exit(1);
		}
		split_free(split_line, 0);
		line = get_next_line(fd);
	}
	close(fd);
	if (main_struct->input.identifier_counter != 6 || map == NULL)
	{
		free_everything(main_struct, &map);
		print_error_message(INFO_MISSING);
		exit(1);
	}
	if (map_to_array(main_struct, map) < 0)
	{
		free_everything(main_struct, &map);
		exit(1);
	}
	free_map_nodes(&map);
}
