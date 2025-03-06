/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:00:53 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/06 12:13:19 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

enum e_location
{
	FLOOR,
	CEILING
};

int	get_color(char *color)
{
	int	number;

	if (color == NULL)
		return (-1);
	number = ft_atoi(color);
	if (number >= 0 && number <= 255)
		return (number);
	return (-1);
}

int	set_rgb(t_rgb *floor_color, char **rgb_split)
{
	int	color;

	color = get_color(rgb_split[0]);
	floor_color->r = color;
	color = get_color(rgb_split[1]);
	floor_color->g = color;
	color = get_color(rgb_split[2]);
	floor_color->b = color;
	return (1);
}

void	parse_color(char *rgb, enum e_location location, t_cub3D *main_struct)
{
	char	**rgb_split;

	rgb_split = ft_split(rgb, ',');
	if (location == FLOOR)
		set_rgb(&(main_struct->input.floor_color), rgb_split);
	else if (location == CEILING)
		set_rgb(&(main_struct->input.ceiling_color), rgb_split);
}

int	set_floor_ceiling(char *type_identifier, char *color_code,
	t_cub3D *main_struct)
{
	if (ft_strncmp("F\0", type_identifier, 2) == 0)
	{
		parse_color(color_code, FLOOR, main_struct);
		return (1);
	}
	else if (ft_strncmp("C\0", type_identifier, 2) == 0)
	{
		parse_color(color_code, CEILING, main_struct);
		return (1);
	}
	return (-1);
}

void	set_wall_texture(char *type_identifier, char *texture,
	t_cub3D *main_struct)
{
	if (ft_strncmp("NO\0", type_identifier, 3) == 0)
		main_struct->input.no_texture = ft_strtrim(texture, "\n");
	else if (ft_strncmp("EA\0", type_identifier, 3) == 0)
		main_struct->input.ea_texture = ft_strtrim(texture, "\n");
	else if (ft_strncmp("SO\0", type_identifier, 3) == 0)
		main_struct->input.so_texture = ft_strtrim(texture, "\n");
	else if (ft_strncmp("WE\0", type_identifier, 3) == 0)
		main_struct->input.we_texture = ft_strtrim(texture, "\n");
}

void	parse_split_line(char **split_line, t_cub3D *main_struct)
{
	set_floor_ceiling(split_line[0], split_line[1], main_struct);
	set_wall_texture(split_line[0], split_line[1], main_struct);
}

void	parse_file(int fd, t_cub3D *main_struct)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		split_line = ft_split(line, ' ');
		free(line);
		parse_split_line(split_line, main_struct);
		line = get_next_line(fd);
	}
}
