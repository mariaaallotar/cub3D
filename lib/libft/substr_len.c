/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:04:33 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 16:04:54 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	substr_len(char *start, char *end)
{
	int	i;

	i = 0;
	while (start != end)
	{
		start++;
		i++;
	}
	return (i);
}
