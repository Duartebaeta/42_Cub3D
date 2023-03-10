/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:01:48 by jocaetan          #+#    #+#             */
/*   Updated: 2023/01/23 20:25:21 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free and NULL an array of strings with the last element being NULL-pointer
*/

void	ft_strarray_clear(char ***str_array)
{
	int	i;

	if (str_array != NULL && *str_array != NULL)
	{
		i = -1;
		while ((*str_array)[++i])
			ft_strdel(&(*str_array)[i]);
		free(*str_array);
		*str_array = NULL;
	}
}
