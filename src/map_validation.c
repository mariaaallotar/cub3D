/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:58:48 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/19 14:26:30 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	validate_line(t_map_line *current)
{
	int		i;
	char	c;

	i = 0;
	while (current->line[i] != '\0' && current->line[i] != '\n')
	{
		c = current->line[i];
		if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		{
			if (check_player(current, i) < 0)
				return (-1);
		}
		else if (c == '0')
		{
			if (check_zero(current, i) < 0)
				return (-1);
		}
		else if (c != '1' && c != ' ')
			return (print_error_message(WRONG_CHAR));
		i++;
	}
	return (1);
}

int	validate_map(t_map_line **map)
{
	t_map_line	*current;

	current = *map;
	while (current)
	{
		if (validate_line(current) < 0)
			return (-1);
		current = current->next;
	}
	return (1);
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
			if ((int)main_struct->draw.player_dir.x == 0
				&& (int)main_struct->draw.player_dir.y == 0)
				set_player(current, main_struct, i, c);
			else
				return (print_error_message(MULT_PLAYER));
		}
		else if (c != '1' && c != '0' && c != ' ')
			return (print_error_message(WRONG_CHAR));
		i++;
	}
	return (1);
}
