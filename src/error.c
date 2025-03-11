/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:07:50 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/11 12:50:01 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	error_and_exit(int return_value)
{
	if (errno != 0)
		perror("Error");
	else if (mlx_errno != 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (return_value == WRONG_RGB_VALUE)
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
	else
		ft_putstr_fd("Error: something went wrong\n", 2);
	exit(1);
}
