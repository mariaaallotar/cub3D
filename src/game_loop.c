/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/18 15:23:14 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	check_keypress(t_cub3D *main_struct, mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		cam_turn_left(main_struct);
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		cam_turn_right(main_struct);
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
		cam_move_fwd(main_struct);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		cam_move_back(main_struct);
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		cam_strafe_left(main_struct);
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		cam_strafe_right(main_struct);
}

static void	game_hook(void *param)
{
	t_cub3D		*main_struct;
	t_draw		*data;
	mlx_t		*mlx;
	mlx_image_t	*image;

	main_struct = param;
	data = &(main_struct->draw);
	mlx = data->mlx;
	image = data->image;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		return ;
	}
	draw(data, main_struct);
	check_keypress(main_struct, mlx);
}

void	start_graphics(int image_width, int image_heigth, t_cub3D *main_struct)
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
	main_struct->draw.mlx = mlx;
	main_struct->draw.image = image;
	main_struct->draw.image_width = image_width;
	main_struct->draw.image_heigth = image_heigth;
	mlx_loop_hook(mlx, game_hook, main_struct);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
