/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/07 15:40:12 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	game_hook(void *param)
{
	// TODO: create a struct thht holds the game data and the mlx objet, so
	// that we can pas it to this function
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

}

void	start_graphics(int image_width, int image_heigth)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(image_width, image_heigth, "cub3D", true);
	// if (!mlx)
		// fdf_cleanup_exit(map);
/* 	image = mlx_new_image(mlx, image_width, image_heigth);
	if (!image)
	{
		mlx_close_window(mlx);
		// fdf_cleanup_exit(map);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) < 0)
	{
		mlx_close_window(mlx);
		// fdf_cleanup_exit(map);
	} */
	mlx_loop_hook(mlx, game_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
