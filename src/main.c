/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/07 14:45:22 by maheleni         ###   ########.fr       */
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
}

void	init_main_struct(t_cub3D *main_struct)
{
	t_input input;

	init_input_struct(&input);
	main_struct->input = input;
}

void	print_input_struct(t_cub3D main_struct)
{
	printf("NO %s\n", main_struct.input.no_texture);
	printf("EA %s\n", main_struct.input.ea_texture);
	printf("SO %s\n", main_struct.input.so_texture);
	printf("WE %s\n", main_struct.input.we_texture);
	printf("F %i,%i,%i\n", main_struct.input.floor_color.r,
		main_struct.input.floor_color.g,
		main_struct.input.floor_color.b);
	printf("C %i,%i,%i\n", main_struct.input.ceiling_color.r,
		main_struct.input.ceiling_color.g,
		main_struct.input.ceiling_color.b);
	
	t_map_line	*map_line = main_struct.input.map;
	while (map_line != NULL)
	{
		printf("%s", map_line->line);
		map_line = map_line->next;
	}
}

void	free_map_list(t_map_line *map)
{
	t_map_line *current;

	current = map;
	while (current != NULL)
	{
		free(current->line);
		if (current->next == NULL)
		{
			free(current);
			break ;
		}
		current = current->next;
		free(current->previous);
	}
}

void	free_everything(t_cub3D	*main_struct)
{
	free(main_struct->input.no_texture);
	free(main_struct->input.ea_texture);
	free(main_struct->input.so_texture);
	free(main_struct->input.we_texture);
	free_map_list(main_struct->input.map);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cub3D	main_struct;

	validate_arguments(argc, argv);
	fd = open_file(argv[1]);
	init_main_struct(&main_struct);
	parse_file(fd, &main_struct);
	print_input_struct(main_struct);
	draw_map();
	free_everything(&main_struct);
	return (0);
}
