/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:49:46 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 15:51:09 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	split_free(char **str, int ret_val)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (ret_val);
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (ret_val);
}

void	*free_strs(char **str1, char **str2)
{
	if (*str1 != NULL)
		free(*str1);
	if (*str2 != NULL)
		free(*str2);
	return (NULL);
}

int	free_strs_int(char **str1, char **str2)
{
	if (*str1 != NULL)
		free(*str1);
	if (*str2 != NULL)
		free(*str2);
	return (-1);
}
