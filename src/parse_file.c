/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:00:53 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/10 16:42:06 by maheleni         ###   ########.fr       */
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
	if (!ft_isdigit(*color))
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
	if (color == -1)
		return (WRONG_RGB_VALUE);
	floor_color->r = color;
	color = get_color(rgb_split[1]);
	if (color == -1)
		return (WRONG_RGB_VALUE);
	floor_color->g = color;
	color = get_color(rgb_split[2]);
	if (color == -1)
		return (WRONG_RGB_VALUE);
	floor_color->b = color;
	return (1);
}

int	parse_color(char *rgb, enum e_location location, t_cub3D *main_struct)
{
	char	**rgb_split;
	t_rgb	*location_data_pointer;
	int		return_value;

	if (location == FLOOR)
		location_data_pointer = &(main_struct->input.floor_color);
	else if (location == CEILING)
		location_data_pointer = &(main_struct->input.ceiling_color);
	else
		return (-1);
	rgb_split = ft_split(rgb, ',');
	if (rgb_split == NULL)
		return (-1);
	return_value = set_rgb(location_data_pointer, rgb_split);
	if (return_value < 0)
	{
		split_free(rgb_split, 0);
		return (return_value);
	}
	if (rgb_split[3] != NULL)
	{
		split_free(rgb_split, 0);
		return (EXTRA_VALUE);
	}
	return (split_free(rgb_split, 1));
}

int	set_floor_ceiling(char *type_identifier, char *color_code,
	t_cub3D *main_struct)
{
	if (ft_strncmp("F\0", type_identifier, 2) == 0)
	{
		if (main_struct->input.floor_color.r != -1)
			return (DOUBLE_COLOR_ID);
		return (parse_color(color_code, FLOOR, main_struct));
	}
	else if (ft_strncmp("C\0", type_identifier, 2) == 0)
	{
		if (main_struct->input.ceiling_color.r != -1)
			return (DOUBLE_COLOR_ID);
		return (parse_color(color_code, CEILING, main_struct));
	}
	return (NOT_IDENTIFIER);
}

int	set_texture(char *texture, mlx_texture_t **texture_location_pointer)
{
	*texture_location_pointer = mlx_load_png(texture);
	free(texture);
	if (*texture_location_pointer == NULL)
		return (-1);
	return (1);
}

int	set_wall_texture(char *type_identifier, char *texture,
	t_cub3D *main_struct)
{
	mlx_texture_t	**texture_location_pointer;
	char			*trimmed_texture;

	if (ft_strncmp("NO\0", type_identifier, 3) == 0)
		texture_location_pointer = &(main_struct->input.no_texture);
	else if (ft_strncmp("EA\0", type_identifier, 3) == 0)
		texture_location_pointer = &(main_struct->input.ea_texture);
	else if (ft_strncmp("SO\0", type_identifier, 3) == 0)
		texture_location_pointer = &(main_struct->input.so_texture);
	else if (ft_strncmp("WE\0", type_identifier, 3) == 0)
		texture_location_pointer = &(main_struct->input.we_texture);
	else
		return (NOT_IDENTIFIER);
	if (*texture_location_pointer != NULL)
		return (DOUBLE_WALL_ID);
	trimmed_texture = ft_strtrim(texture, "\n");
	if (trimmed_texture == NULL)
		return (-1);
	if (set_texture(trimmed_texture, texture_location_pointer) < 0)
		return (-1);
	return (1);
}

void	init_map_line(t_map_line *current, char *line, t_map_line *previous)
{
	current->line = line;
	current->length = ft_strlen(line);
	current->previous = previous;
	current->next = NULL;
}

void	set_map(char *line, int fd, t_cub3D *main_struct)
{
	t_map_line	*current;
	t_map_line	*previous;

	previous = NULL;
	while (line != NULL)
	{
		current = malloc (sizeof(t_map_line));
		//check fail
		if (previous != NULL)
			previous->next = current;
		init_map_line(current, line, previous);
		if (main_struct->input.map == NULL)
			main_struct->input.map = current;
		previous = current;
		line = get_next_line(fd);
	}
}

int	start_of_map(char *line)
{
	char	*word;

	//if (all_id_found())		//TODO
	//	return (1);
	word = get_word(line);
	//check if it failed
	if (word[0] == '1')
	{
		free(word);
		return (1);
	}
	free(word);
	return (0);
}

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

//ALLOCATES split_line
void	parse_file(int fd, t_cub3D *main_struct)
{
	char		*line;
	char		**split_line;
	int			return_value;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (start_of_map(line))
		{
			set_map(line, fd, main_struct);
			break ;
		}
		if (*line == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		split_line = ft_split(line, ' ');
		free(line);
		return_value = parse_split_line(split_line, main_struct);
		if (return_value < 0)
		{
			split_free(split_line, 0);
			free_everything(main_struct);
			error_and_exit(return_value);
		}
		split_free(split_line, 0);
		line = get_next_line(fd);
	}
}
