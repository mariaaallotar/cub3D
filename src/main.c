/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/11 11:27:40 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	kbd_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static void	start_graphics(int image_width, int image_heigth)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(image_width, image_heigth, "cub3D", true);
	// if (!mlx)
		// fdf_cleanup_exit(map);
	image = mlx_new_image(mlx, image_width, image_heigth);
	if (!image)
	{
		mlx_close_window(mlx);
		// fdf_cleanup_exit(map);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		mlx_close_window(mlx);
		// fdf_cleanup_exit(map);
	}
	mlx_loop_hook(mlx, kbd_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

static void	draw_map()
{
	int		image_width;
	int		image_heigth;

	image_width = 1600;
	image_heigth = 1000;
	start_graphics(image_width, image_heigth);
}

static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Could not open file\n", 2);
		exit (1);
	}
	return (fd);
}

void	init_input_struct(t_input *input)
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

void	init_main_struct(t_cub3D *main_struct)
{
	t_input input;

	init_input_struct(&input);
	main_struct->input = input;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cub3D	main_struct;

	validate_arguments(argc, argv);
	fd = open_file(argv[1]);
	init_main_struct(&main_struct);
	parse_file(fd, &main_struct);
	draw_map();
	free_everything(&main_struct, NULL);
	return (0);
}
