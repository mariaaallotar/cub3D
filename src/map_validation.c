/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:58:48 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/12 16:49:15 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	get_chars(t_chars *chars, t_map_line *current, int i)
{
	if (i > 0)
		chars->left = current->line[i - 1];
	else
		chars->left = ' ';
	if (i >= current->length - 1)
		chars->right = ' ';
	else
		chars->right = current->line[i + 1];
	if (current->previous != NULL && i < current->previous->length)
		chars->up = current->previous->line[i];
	else
		chars->up = ' ';
	if (current->next != NULL && i < current->next->length)
		chars->down = current->next->line[i];
	else
		chars->down = ' ';
}

int	check_zero(t_map_line *current, int i)
{
	t_chars	chars;

	get_chars(&chars, current, i);
	if (chars.left == ' ' || chars.right == ' ' ||
		chars.up == ' ' || chars.down == ' ')
		return (WALL_ERROR);
	return (1);
}

int	check_player(t_map_line *current, int i)
{
	t_chars	chars;

	get_chars(&chars, current, i);
	if (chars.left == ' ' || chars.right == ' ' ||
		chars.up == ' ' || chars.down == ' ')
		return (WALL_ERROR);
	return (1);
}

int	validate_line(t_map_line *current)
{
	int		i;
	char	c;
	int		return_value;

	i = 0;
	while (current->line[i] != '\0' && current->line[i] != '\n')
	{
		c = current->line[i];
		if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		{
			return_value = check_player(current, i);
			if (return_value < 0)
				return (return_value);
		}
		else if (c == '0')
		{
			return_value = check_zero(current, i);
			if (return_value < 0)
				return (return_value);
		}
		else if (c != '1' && c != ' ')
			return (WRONG_CHAR);
		i++;
	}
	return (1);
}

//TODO insted of returning an error number, have the functions call a error message function
//and then just return -1. Would eliminate all return_value variables

int	validate_map(t_map_line **map)
{
	t_map_line	*current;
	int			return_value;
	
	current = *map;
	while (current)
	{
		return_value = validate_line(current);
		if (return_value < 0)
			return (return_value);
		current = current->next;
	}
	return (1);
}

void	set_player_direction(char direction, t_cub3D *main_struct)
{
	int	x;
	int	y;

	if (direction == 'N')
	{
		x = 0;
		y = -1;
	}
	else if (direction == 'E')
	{
		x = 1;
		y = 0;
	}
	else if (direction == 'S')
	{
		x = 0;
		y = 1;
	}
	else
	{
		x = -1;
		y = 0;
	}
	main_struct->draw.player_dir.x = x;
	main_struct->draw.player_dir.y = y;
}

void	set_player(t_map_line *current, t_cub3D *main_struct, int i,
	char direction)
{
	main_struct->draw.player_pos.x = i;
	i = 0;
	while (current->previous != NULL)
	{
		i++;
		current = current->previous;
	}
	main_struct->draw.player_pos.y = i;
	set_player_direction(direction, main_struct);
	
}

int	check_forbidden_chars(t_map_line *current, t_cub3D *main_struct)
{
	int		i;
	char	c;

	i = 0;
	while (current->line[i] != '\0' && current->line[i] != '\n')
	{
		c = current->line[i];
		if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		{
			if ((int)main_struct->draw.player_dir.x == 0 &&
				(int)main_struct->draw.player_dir.y == 0)
				set_player(current, main_struct, i, c);
			else
				return (MULT_PLAYER);
		}
		else if (c != '1' && c != '0' && c != ' ')
			return (WRONG_CHAR);
		i++;
	}
	return (1);
}
