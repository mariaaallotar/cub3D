/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:00:14 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/05 16:33:40 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return null if allocation fails
// in other fail cases return an empty string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_str;

	if (!s)
		return (0);
	len_str = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strndup("", 0));
	if (len_str - start < len)
		return (ft_strndup(&s[start], len_str - start));
	return (ft_strndup(&s[start], len));
}
