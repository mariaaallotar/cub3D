/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:20:31 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/12 15:33:43 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	set_map_line(t_map_line *current, char *line, t_map_line *previous,
	t_cub3D *main_struct)
{
	int	return_value;

	current->line = line;
	current->length = ft_strlen(line);
	if (line[current->length - 1] == '\n')
		current->length--;
	current->previous = previous;
	current->next = NULL;
	return_value = check_forbidden_chars(current, main_struct);
	if (return_value < 0)
		return (return_value);
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

int	set_map(char *line, int fd, t_map_line **map, t_cub3D *main_struct)
{
	t_map_line	*current;
	t_map_line	*previous;
	int			return_value;

	previous = NULL;
	while (line != NULL)
	{
		if (*(skip_whitespace(line)) == '\0')
		{
			free(line);
			if (rest_is_whitespace(fd))
				break ;
			return (NEWLINE_IN_MAP);
		}
		current = malloc (sizeof(t_map_line));
		if (current == NULL)
			return (-1);
		if (previous != NULL)
			previous->next = current;
		return_value = set_map_line(current, line, previous, main_struct);
		if (return_value < 0)
			return (return_value);
		if (*map == NULL)
			*map = current;
		previous = current;
		line = get_next_line(fd);
	}
	if (main_struct->draw.player_dir.x == 0 &&
		main_struct->draw.player_dir.y == 0)
		return (NO_PLAYER);
	return_value = validate_map(map);
	if (return_value < 0)
		return (return_value);
	return (1);
}

int	start_of_map(char **line, t_cub3D *main_struct)
{
	char	*word;

	if (main_struct->input.identifier_counter == 6)
		return (1);
	word = get_word(*line);
	if (word == NULL)
	{
		free(*line);
		free_everything(main_struct, NULL);
		error_and_exit(1);
	}
	if (word[0] == '1')
	{
		free(word);
		return (1);
	}
	free(word);
	return (0);
}
