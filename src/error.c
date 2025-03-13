/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:07:50 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/13 19:41:27 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	map_errors(int return_value)
{
	if (return_value == WRONG_CHAR)
		ft_putstr_fd("Error: unexpected character in map\n", 2);
	else if (return_value == WALL_ERROR)
		ft_putstr_fd("Error: map not surrounded by walls\n", 2);
	else if (return_value == MULT_PLAYER)
		ft_putstr_fd("Error: multiple players found\n", 2);
	else if (return_value == NO_PLAYER)
		ft_putstr_fd("Error: no player in map\n", 2);
	else if (return_value == NEWLINE_IN_MAP)
		ft_putstr_fd("Error: map has an empty line\n", 2);
	else if (return_value == PLAYER_OUTSIDE)
		ft_putstr_fd("Error: player must be inside of map\n", 2);
}

void	identifier_errors(int return_value)
{
	if (return_value == WRONG_RGB_VALUE)
		ft_putstr_fd("Error: incorrect rgb value\n", 2);
	else if (return_value == EXTRA_VALUE)
		ft_putstr_fd("Error: extra value after identifier\n", 2);
	else if (return_value == NOT_IDENTIFIER)
		ft_putstr_fd("Error: identifier not supported\n", 2);
	else if (return_value == DOUBLE_COLOR_ID)
		ft_putstr_fd("Error: several floor and/or ceiling color identifiers found\n", 2);
	else if (return_value == DOUBLE_WALL_ID)
		ft_putstr_fd("Error: several of one wall texture identifier found\n", 2);
	else if (return_value == MAP_NOT_LAST)
		ft_putstr_fd("Error: map before all identifiers\n", 2);
	else if (return_value == INFO_MISSING)
		ft_putstr_fd("Error: file does not have all necessary information\n", 2);
	else if (return_value == IDENTIFIER_WITHOUT_VALUE)
		ft_putstr_fd("Error: every identifer needs a value\n", 2);
}

int	print_error_message(int return_value)
{
	if (mlx_errno != 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (errno != 0)
		perror("Error");
	identifier_errors(return_value);
	map_errors(return_value);
	return (-1);
}
