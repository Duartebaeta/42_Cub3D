/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:01:48 by jocaetan          #+#    #+#             */
/*   Updated: 2023/05/30 16:34:46 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
	array = ft_calloc(size + 1, sizeof(char*));
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
	while (s[l] != NULL)
		l++;
	return (l);
}
