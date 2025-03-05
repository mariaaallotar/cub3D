/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:41:08 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 13:03:55 by lemercie         ###   ########.fr       */
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

	mlx = mlx_init(image_width, image_heigth, "FdF", true);
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

int	main(int argc, char **argv)
{
	int	fd;

	validate_arguments(argc, argv);
	fd = open_file(argv[1]);
	draw_map(); 
	return (0);
}
