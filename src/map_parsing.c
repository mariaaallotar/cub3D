/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:20:31 by maheleni          #+#    #+#             */
/*   Updated: 2025/03/11 12:20:52 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_map_line(t_map_line *current, char *line, t_map_line *previous)
{
	current->line = line;
	current->length = ft_strlen(line);
	current->previous = previous;
	current->next = NULL;
}

void	set_map(char *line, int fd, t_map_line **map)
{
	t_map_line	*current;
	t_map_line	*previous;

	previous = NULL;
	while (line != NULL)
	{
		current = malloc (sizeof(t_map_line));
		//check fail
		if (previous != NULL)
			previous->next = current;
		init_map_line(current, line, previous);
		if (*map == NULL)
			*map = current;
		previous = current;
		line = get_next_line(fd);
	}
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