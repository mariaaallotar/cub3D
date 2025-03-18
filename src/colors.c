/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:06:13 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/18 16:07:30 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// a = 255 means full opacity
int32_t	convert_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// the *4 +1 +2 and +3 is due to how data is stored in mlx_texture_t
// it is actually an array of 4* the number of pixels in the image
// where each number represents one color channel of one pixel
unsigned int	get_color_from_texture(mlx_texture_t *texture, int tex_x,
											int tex_y)
{
	return (convert_color(
			texture->pixels[(texture->width * tex_y + tex_x) * 4],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 1],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 2],
			texture->pixels[((texture->width * tex_y + tex_x) * 4) + 3]
		));
}
