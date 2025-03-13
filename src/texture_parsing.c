/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:18:38 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/11 13:12:53 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	set_texture(char *texture, mlx_texture_t **texture_location_pointer)
{
	*texture_location_pointer = mlx_load_png(texture);
	free(texture);
	if (*texture_location_pointer == NULL)
		return (-1);
	return (1);
}

int	set_texture_location_pointer(char *type_identifier,
	mlx_texture_t ***texture_location_pointer,t_cub3D *main_struct)
{
	if (ft_strncmp("NO\0", type_identifier, 3) == 0 ||
		ft_strncmp("NO\n", type_identifier, 3) == 0)
		*texture_location_pointer = &(main_struct->input.no_texture);
	else if (ft_strncmp("EA\0", type_identifier, 3) == 0 ||
		ft_strncmp("EA\n", type_identifier, 3) == 0)
		*texture_location_pointer = &(main_struct->input.ea_texture);
	else if (ft_strncmp("SO\0", type_identifier, 3) == 0 ||
		ft_strncmp("SO\n", type_identifier, 3) == 0)
		*texture_location_pointer = &(main_struct->input.so_texture);
	else if (ft_strncmp("WE\0", type_identifier, 3) == 0 ||
		ft_strncmp("WE\n", type_identifier, 3) == 0)
		*texture_location_pointer = &(main_struct->input.we_texture);
	else
		return (NOT_IDENTIFIER);
	return (1);
}

int	set_wall_texture(char *type_identifier, char *texture,
	t_cub3D *main_struct)
{
	mlx_texture_t	**texture_location_pointer;
	char			*trimmed_texture;
	int				return_value;

	texture_location_pointer = NULL;
	return_value = set_texture_location_pointer(type_identifier,
		&texture_location_pointer, main_struct);
	if (return_value < 0)
		return (return_value);
	if (*texture_location_pointer != NULL)
		return (DOUBLE_WALL_ID);
	if (texture == NULL || *texture == '\n')
		return(IDENTIFIER_WITHOUT_VALUE);
	trimmed_texture = ft_strtrim(texture, "\n");
	if (trimmed_texture == NULL)
		return (-1);
	if (set_texture(trimmed_texture, texture_location_pointer) < 0)
		return (-1);
	main_struct->input.identifier_counter++;
	return (1);
}
