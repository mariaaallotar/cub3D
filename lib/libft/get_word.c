/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:05:32 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 16:05:56 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_word(char *start)
{
	char	*end;

	start = skip_whitespace(start);
	end = start;
	while (*end && !is_whitespace(*end))
	{
		end++;
	}
	return (ft_strndup(start, substr_len(start, end)));
}
