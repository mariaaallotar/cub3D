/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:23:53 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 12:24:49 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	has_cub_extension(char *filename)
{
	char	*last_dot;

	if (ft_strlen(filename) < 4)
		return (false);
	last_dot = ft_strrchr(filename, '.');
	if (!last_dot)
		return (false);
	if (ft_strncmp(last_dot, ".cub", 5) == 0)
		return (true);
	return (false);
}

void	validate_arguments(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf("Error: Filename missing\n");
		exit(1);
	}
	if (argc > 2)
	{
		ft_printf("Error: Too many arguments\n");
		exit(1);
	}
	if (!has_cub_extension(argv[1]))
	{
		ft_printf("Error: this is not a .cub file\n");
		exit(1);
	}
}
