/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:54 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/19 14:26:08 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	get_chars(t_chars *chars, t_map_line *current, int i)
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
	if (chars.left == ' ' || chars.right == ' '
		|| chars.up == ' ' || chars.down == ' ')
		return (print_error_message(WALL_ERROR));
	return (1);
}

int	check_player(t_map_line *current, int i)
{
	t_chars	chars;

	get_chars(&chars, current, i);
	if (chars.left == ' ' || chars.right == ' '
		|| chars.up == ' ' || chars.down == ' ')
		return (print_error_message(WALL_ERROR));
	return (1);
}

int	rest_is_whitespace(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*(skip_whitespace(line)) != '\0')
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
