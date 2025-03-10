/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:07:50 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/10 16:42:30 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	error_and_exit(int return_value)
{
	if (errno != 0)
		perror("Error");
	else if (mlx_errno != 0)
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
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
	else
		ft_putstr_fd("Error: something went wrong\n", 2);
	exit(1);
}
