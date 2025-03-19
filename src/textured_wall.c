/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:47:14 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/19 14:56:44 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	calc_wall_heigth(t_draw *draw, t_rcast *rcast)
{
	rcast->wall_heigth = draw->image_heigth / rcast->perp_wall_dist;
	rcast->start_draw = -rcast->wall_heigth / 2 + draw->image_heigth / 2;
	if (rcast->start_draw < 0)
		rcast->start_draw = 0;
	rcast->end_draw = rcast->wall_heigth / 2 + draw->image_heigth / 2;
	if (rcast->end_draw > draw->image_heigth)
		rcast->end_draw = draw->image_heigth -1;
}

static void	calc_wall_x(t_rcast *rcast, t_draw *draw)
{
	if (rcast->wall_side == 0)
	{
		rcast->wall_x = draw->player_pos.y + rcast->perp_wall_dist
			* rcast->ray_dir.y;
	}
	else
	{
		rcast->wall_x = draw->player_pos.x + rcast->perp_wall_dist
			* rcast->ray_dir.x;
	}
	rcast->wall_x -= floor(rcast->wall_x);
}

// the if-statement here mirrors some of the textures in some situations
static void	find_pos_in_texture(mlx_texture_t *texture,
								t_rcast *rcast, t_draw *draw)
{
	rcast->tex_x = rcast->wall_x * (double) texture->width;
	if ((rcast->wall_side == 0 && rcast->ray_dir.x < 0)
		|| (rcast->wall_side == 1 && rcast->ray_dir.y > 0))
	{
		rcast->tex_x = texture->width - rcast->tex_x - 1;
	}
	rcast->tex_y_step = (double) texture->height / rcast->wall_heigth;
	rcast->tex_pos = (rcast->start_draw - draw->image_heigth
			/ 2.0 + rcast->wall_heigth / 2.0) * rcast->tex_y_step;
}

static void	draw_with_texture(mlx_texture_t *texture, t_rcast *rcast,
								t_draw *draw, int cur_screen_col)
{
	int				i;
	unsigned int	tex_y;
	unsigned int	color;

	i = rcast->start_draw;
	while (i <= rcast->end_draw)
	{
		tex_y = rcast->tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		rcast->tex_pos += rcast->tex_y_step;
		color = get_color_from_texture(texture, rcast->tex_x, tex_y);
		if (cur_screen_col >= 0
			&& (unsigned int) cur_screen_col < draw->image->width
			&& i >= 0 && (unsigned int) i < draw->image->height)
		{
			mlx_put_pixel(draw->image, cur_screen_col, i, color);
		}
		i++;
	}
}

void	draw_wall_column_tex(t_cub3D *main_struct, t_rcast *rcast,
									int cur_screen_col)
{
	t_draw			*draw;
	mlx_texture_t	*texture;

	draw = &main_struct->draw;
	calc_wall_heigth(&main_struct->draw, rcast);
	calc_wall_x(rcast, &main_struct->draw);
	texture = pick_texture(main_struct, rcast->wall_side, rcast->step_dir);
	find_pos_in_texture(texture, rcast, draw);
	draw_with_texture(texture, rcast, draw, cur_screen_col);
}
