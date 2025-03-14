/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:24 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/14 11:35:38 by lemercie         ###   ########.fr       */
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

// 0xFF as last argument for convert_color() stands for full opacity
// (alpha channel
void	draw_floor_and_ceiling(t_cub3D *main_struct)
{
	int	color_ceiling;
	int	color_floor;
	int	x;
	int	y;

	color_ceiling = convert_color(main_struct->input.ceiling_color.r,
							   main_struct->input.ceiling_color.g,
							   main_struct->input.ceiling_color.b,
							   0xFF);
	color_floor = convert_color(main_struct->input.floor_color.r,
							   main_struct->input.floor_color.g,
							   main_struct->input.floor_color.b,
							   0xFF);
	x = 0;
	while (x < main_struct->draw.image_width)
	{
		y = 0;
		while (y < main_struct->draw.image_heigth)
		{
			if (y < main_struct->draw.image_heigth / 2)
			{
				mlx_put_pixel(main_struct->draw.image, x, y, color_ceiling);
			}
			else
			{
				mlx_put_pixel(main_struct->draw.image, x, y, color_floor);
			}
			y++;
		}
		x++;
	}
}


