/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/12 13:29:17 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	testMap[24][24] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	testMap2[24][24] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static void	draw(mlx_image_t *image, t_draw *data)
{
	draw_floor_and_ceiling(image, data);
	int	cur_screen_col = 0;
	while (cur_screen_col < data->image_width)
	{
		double	camera_x = 2 * cur_screen_col / (double) data->image_width - 1;
		t_point_double	ray_dir;
		ray_dir.x = data->player_dir.x + data->camera_plane.x * camera_x;
		ray_dir.y = data->player_dir.y + data->camera_plane.y * camera_x;

		// which tile we're in
		t_point_int	ray_pos;
		ray_pos.x = (int) data->player_pos.x;
		ray_pos.y = (int) data->player_pos.y;

		// distance to first tile side we encounter
		t_point_double	ray_dist_to_side;

		// step distance between tile boundaries
		t_point_double	ray_step_dist;

		if (ray_dir.x == 0)//to avoid divison by zero
		{
			ray_step_dist.x = 1e30; 
		}
		else
		{
			//can be simplified
			// ray_step_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
			ray_step_dist.x = fabs(1/ray_dir.x);
		}
		if (ray_dir.y == 0)//to avoid divison by zero
		{
			ray_step_dist.y = 1e30;
		}
		else
		{
			// can be simplified
			// ray_step_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
			ray_step_dist.y = fabs(1/ray_dir.y);
		}

		// are we moving is positive or negative direction on the axis?
		t_point_int step_dir;
		if (ray_dir.x < 0)
		{
			step_dir.x = -1;
			ray_dist_to_side.x = (data->player_pos.x - ray_pos.x) * ray_step_dist.x;
		}
		else
		{
			step_dir.x = 1;
			ray_dist_to_side.x = (ray_pos.x + 1.0 - data->player_pos.x) * ray_step_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step_dir.y = -1;
			ray_dist_to_side.y = (data->player_pos.y - ray_pos.y) * ray_step_dist.y;
		}
		else
		{
			step_dir.y = 1;
			ray_dist_to_side.y = (ray_pos.y + 1.0 - data->player_pos.y) * ray_step_dist.y;
		}
	
		// DDA part
		bool	wall_hit;
		int		wall_side;

		wall_hit = false;
		while (wall_hit == false)
		{
			if (ray_dist_to_side.x < ray_dist_to_side.y)
			{
				ray_dist_to_side.x += ray_step_dist.x;
				ray_pos.x += step_dir.x;
				wall_side = 0;
			}
			else
			{
				ray_dist_to_side.y += ray_step_dist.y;
				ray_pos.y += step_dir.y;
				wall_side = 1;
			}
			if (testMap[ray_pos.y][ray_pos.x] > 0)
			{
				wall_hit = true;
			}
		}

		// calculate distance of wall to camera plane, not to player. This
		// avoid fish eye effect
		double	perpendicular_wall_dist;
		if (wall_side == 0)
		{
			perpendicular_wall_dist = ray_dist_to_side.x - ray_step_dist.x;
		}
		else
		{
			perpendicular_wall_dist = ray_dist_to_side.y - ray_step_dist.y;
		}
	
		int wall_heigth;
		wall_heigth = data->image_heigth / perpendicular_wall_dist;

		int	start_draw;
		start_draw = -wall_heigth / 2 + data->image_heigth / 2;
		if (start_draw < 0)
			start_draw = 0;
		int	end_draw;
		end_draw = wall_heigth / 2 + data->image_heigth /2;
		if (end_draw > data->image_heigth)
			end_draw = data->image_heigth -1;

		int	color;
		if (wall_side == 0)
		{
			color = 0xFF0000FF;
		}
		else
		{
			color = 0x990000FF;
		}
		draw_vert_line(image, cur_screen_col, start_draw, end_draw, color);
		cur_screen_col++;
	}
}

static void	game_hook(void *param)
{
	t_draw		*data;
	mlx_t		*mlx;
	mlx_image_t	*image;

	data = param;
	mlx = data->mlx;
	image = data->image;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		return ;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		cam_turn_left(data);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		cam_turn_right(data);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		cam_move_fwd(data);
		
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		cam_move_back(data);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		cam_strafe_left(data);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		cam_strafe_right(data);
	}
	// prevent player from escaping map
	if (data->player_pos.x < 1)
		data->player_pos.x = 1;
	if (data->player_pos.x > 22)
		data->player_pos.x = 22;
	if (data->player_pos.y < 1)
		data->player_pos.y = 1;
	if (data->player_pos.y > 22)
		data->player_pos.y = 22;
	draw(image, data);
}

void	start_graphics(int image_width, int image_heigth)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_draw		data;

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
	data.mlx = mlx;
	data.image = image;
	data.image_width = image_width;
	data.image_heigth = image_heigth;
	data.player_pos.x = 5;
	data.player_pos.y = 12;
	data.player_dir.x = 1;
	data.player_dir.y = 0;
	data.camera_plane.x = 0;
	data.camera_plane.y = g_fov;

	draw(image, &data);
	mlx_loop_hook(mlx, game_hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
