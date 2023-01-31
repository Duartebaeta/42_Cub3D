/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:41:45 by jocaetan          #+#    #+#             */
/*   Updated: 2023/01/31 16:22:12 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*protected_calloc(size_t count, size_t size)
{
	void	*ptr;

	errno = ENOMEM;
	ptr = ft_calloc(count, size);
	if (!ptr)
		program_errors("Malloc", true, true);
	return (ptr);
}

bool	ft_isspace(int c)
{
	if (c == '\t')
		return (true);
	if (c == '\n')
		return (true);
	if (c == '\v')
		return (true);
	if (c == '\f')
		return (true);
	if (c == '\r')
		return (true);
	if (c == ' ')
		return (true);
	else
		return (false);
}

bool	is_map_char(char c)
{
	if (c && !ft_isspace(c))
		return (true);
	return (false);
}

int	array_len(char **array)
{
	int	counter;

	counter = 0;
	while (array[counter] != NULL)
		counter++;
	return (counter);
}
