/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnepfumb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 11:40:19 by mnepfumb          #+#    #+#             */
/*   Updated: 2017/10/06 10:46:42 by mnepfumb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len_one;
	size_t	len_two;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_one = ft_strlen((const char*)s1);
	len_two = ft_strlen((const char*)s2);
	if ((result = (char *)ft_memalloc(sizeof(char) *
					len_one + len_two + 1)) == NULL)
	{
		return (NULL);
	}
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	ft_strcat(result, "\0");
	return (result);
}
