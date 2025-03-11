/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:24 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/11 18:12:41 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_vert_line(mlx_image_t *image, int x, int start_y, int end_y, \
					uint32_t color)
{
	while (start_y < end_y)
	{
		mlx_put_pixel(image, x, start_y, color);
		start_y++;
	}
}

void	draw_floor_and_ceiling(mlx_image_t *image, t_draw *data)
{
	int	color_ceiling;
	int	color_floor;
	int	x;
	int	y;

	color_ceiling = 0x00FF00FF;
	color_floor = 0x0000FFFF;
	x = 0;
	while (x < data->image_width)
	{
		y = 0;
		while (y < data->image_heigth)
		{
			if (y < data->image_heigth / 2)
			{
				mlx_put_pixel(image, x, y, color_ceiling);
			}
			else
			{
				mlx_put_pixel(image, x, y, color_floor);
			}
			y++;
		}
		x++;
	}
}


