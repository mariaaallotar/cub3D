/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/19 11:28:41 by maheleni         ###   ########.fr       */
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

void	game_hook(void *param)
{
	t_cub3D		*main_struct;
	t_draw		*data;
	mlx_t		*mlx;

	main_struct = param;
	data = &(main_struct->draw);
	mlx = data->mlx;
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
	if (!mlx)
	{
		print_error_message(-1);
		return ;
	}
	image = mlx_new_image(mlx, image_width, image_heigth);
	if (!image || mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		if (image != NULL)
			mlx_delete_image(mlx, image);
		print_error_message(-1);
		mlx_close_window(mlx);
		mlx_terminate(mlx);
		return ;
	}
	main_struct->draw.mlx = mlx;
	main_struct->draw.image = image;
	main_struct->draw.image_width = image_width;
	main_struct->draw.image_heigth = image_heigth;
}
