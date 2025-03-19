/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:17:02 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/19 10:13:47 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		return (print_error_message(WRONG_RGB_VALUE));
	floor_color->r = color;
	color = get_color(rgb_split[1]);
	if (color == -1)
		return (print_error_message(WRONG_RGB_VALUE));
	floor_color->g = color;
	color = get_color(rgb_split[2]);
	if (color == -1)
		return (print_error_message(WRONG_RGB_VALUE));
	floor_color->b = color;
	return (1);
}

int	parse_color(char *rgb, enum e_location location, t_cub3D *main_struct)
{
	char	**rgb_split;
	t_rgb	*location_data_pointer;

	if (location == FLOOR)
		location_data_pointer = &(main_struct->input.floor_color);
	else if (location == CEILING)
		location_data_pointer = &(main_struct->input.ceiling_color);
	else
		return (-1);
	rgb_split = ft_split(rgb, ',');
	if (rgb_split == NULL)
		return (print_error_message(-1));
	if (set_rgb(location_data_pointer, rgb_split) < 0)
		return (split_free(rgb_split, -1));
	if (rgb_split[3] != NULL)
	{
		split_free(rgb_split, 1);
		return (print_error_message(EXTRA_VALUE));
	}
	main_struct->input.identifier_counter++;
	return (split_free(rgb_split, 1));
}

int	set_floor_ceiling(char *type_identifier, char *color_code,
	t_cub3D *main_struct)
{
	if (ft_strncmp("F\0", type_identifier, 2) == 0)
	{
		if (main_struct->input.floor_color.r != -1)
			return (print_error_message(DOUBLE_COLOR_ID));
		return (parse_color(color_code, FLOOR, main_struct));
	}
	else if (ft_strncmp("C\0", type_identifier, 2) == 0)
	{
		if (main_struct->input.ceiling_color.r != -1)
			return (print_error_message(DOUBLE_COLOR_ID));
		return (parse_color(color_code, CEILING, main_struct));
	}
	return (print_error_message(NOT_IDENTIFIER));
}
