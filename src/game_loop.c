/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:33:57 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/10 15:59:48 by lemercie         ###   ########.fr       */
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

typedef struct s_point_double
{
	double	x;
	double	y;
}	t_point_double;

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

static void draw_vert_line(mlx_image_t *image, int x, int start_y, int end_y, uint32_t color)
{
	while (start_y < end_y)
	{
		mlx_put_pixel(image, x, start_y, color);
		start_y++;
	}
}

typedef struct s_draw
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			image_width;
	int			image_heigth;
} t_draw;

static void	draw(mlx_image_t *image, int image_width, int image_heigth)
{
	t_point_double	player_pos;
	t_point_double	player_dir;
	t_point_double	camera_plane;

	player_pos.x = 14;
	player_pos.y = 10;
	player_dir.x = -1;
	player_dir.y = 0;
	camera_plane.x = 0;
	camera_plane.y = 0.66;

	int	cur_screen_col = 0;
	while (cur_screen_col < image_width)
	{
		double	camera_x = 2 * cur_screen_col / (double) image_width - 1;
		t_point_double	ray_dir;
		ray_dir.x = player_dir.x + camera_plane.x * camera_x;
		ray_dir.y = player_dir.y + camera_plane.y * camera_x;

		// which tile we're in
		t_point_int	ray_pos;
		ray_pos.x = (int) player_pos.x;
		ray_pos.y = (int) player_pos.y;

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
			ray_step_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		}
		if (ray_dir.y == 0)//to avoid divison by zero
		{
			ray_step_dist.y = 1e30;
		}
		else
		{
			// can be simplified
			ray_step_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
		}

		// are we moving is positive or negative direction on the axis?
		t_point_int step_dir;
		if (ray_dir.x < 0)
		{
			step_dir.x = -1;
			ray_dist_to_side.x = (player_pos.x  - ray_pos.x) * ray_step_dist.x;
		}
		else
		{
			step_dir.x = 1;
			ray_dist_to_side.x = (ray_pos.x + 1.0 - player_pos.x) * ray_step_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step_dir.y = -1;
			ray_dist_to_side.y = (player_pos.y - ray_pos.y) * ray_step_dist.y;
		}
		else
		{
			step_dir.y = 1;
			ray_dist_to_side.y = (ray_pos.y + 1.0 - player_pos.y) * ray_step_dist.y;
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
				ray_pos.y = step_dir.y;
				wall_side = 1;
			}
			if (testMap[ray_pos.x][ray_pos.y] > 0)
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
		wall_heigth = image_heigth / perpendicular_wall_dist;

		int	start_draw;
		start_draw = -wall_heigth / 2 + image_heigth / 2;
		if (start_draw < 0)
			start_draw = 0;
		int	end_draw;
		end_draw = wall_heigth / 2 + image_heigth /2;
		if (end_draw > image_heigth)
			end_draw = image_heigth -1;

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
		mlx_close_window(mlx);
	draw(image, data->image_width, data->image_heigth);
}

void	start_graphics(int image_width, int image_heigth)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_draw		draw;

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
	draw.mlx = mlx;
	draw.image = image;
	draw.image_width = image_width;
	draw.image_heigth = image_heigth;
	mlx_loop_hook(mlx, game_hook, &draw);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
