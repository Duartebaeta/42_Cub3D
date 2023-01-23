/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <marvin@42.fr>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:01:48 by jocaetan          #+#    #+#             */
/*   Updated: 2022/04/28 10:50:41 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_str2dlen(char **s);

/*
**	Free and NULL an array of strings with the last element being NULL-pointer
*/

char	**ft_strarray_dup(char **str_array)
{
	size_t	i;
	size_t	size;
	char	**array;

	size = ft_str2dlen(str_array);
	array = ft_calloc(size, sizeof(char*) + 1);
	i = -1;
	while (++i < size)
		array[i] = ft_strdup(str_array[i]);
	array[i] = '\0';
	return (array);	
}

static size_t	ft_str2dlen(char **s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}
