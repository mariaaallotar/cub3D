/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:44:45 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 16:31:46 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i_start;
	int	i_end;

	if (!s1 || !set)
		return (0);
	if (ft_strlen(s1) == 0)
		return (ft_strndup("", 0));
	if (ft_strlen(set) == 0)
		return (ft_strndup(s1, ft_strlen(s1)));
	i_start = 0;
	while (ft_strchr(set, s1[i_start]))
	{
		i_start++;
	}
	i_end = (int) ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i_end]))
	{
		i_end--;
		if (i_end < 1)
			return (ft_strndup("", 0));
	}
	return (ft_strndup(&s1[i_start], (i_end - i_start) + 1));
}
