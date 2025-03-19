/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/19 16:05:33 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_game(t_cub3D *main_struct)
{
	int		image_width;
	int		image_heigth;

	image_width = 1920;
	image_heigth = 1080;
	start_graphics(image_width, image_heigth, main_struct);
	mlx_loop_hook(main_struct->draw.mlx, game_hook, main_struct);
	mlx_loop(main_struct->draw.mlx);
}

static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error_message(-1);
		exit(1);
	}
	return (fd);
}

static void	init_input_struct(t_input *input)
{
	input->ceiling_color.r = -1;
	input->ceiling_color.g = -1;
	input->ceiling_color.b = -1;
	input->floor_color.r = -1;
	input->floor_color.g = -1;
	input->floor_color.b = -1;
	input->no_texture = NULL;
	input->ea_texture = NULL;
	input->so_texture = NULL;
	input->we_texture = NULL;
	input->map = NULL;
	input->identifier_counter = 0;
}

static void	init_main_struct(t_cub3D *main_struct)
{
	init_input_struct(&(main_struct->input));
	main_struct->draw.player_dir.x = 0;
	main_struct->draw.player_dir.y = 0;
	main_struct->input.map = NULL;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cub3D	main_struct;

	validate_arguments(argc, argv);
	fd = open_file(argv[1]);
	init_main_struct(&main_struct);
	parse_input(fd, &main_struct);
	init_game(&main_struct);
	free_everything(&main_struct, NULL);
	mlx_delete_image(main_struct.draw.mlx, main_struct.draw.image);
	mlx_terminate(main_struct.draw.mlx);
	return (0);
}
