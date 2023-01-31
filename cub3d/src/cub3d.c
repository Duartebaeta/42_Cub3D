/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:40:25 by jocaetan          #+#    #+#             */
/*   Updated: 2023/01/31 21:50:57 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (NUM_ARGS);
	printf("%i\n", arg_checker(argv[1]));
	check_map();
	clear_data();
	return (EXIT_SUCCESS);
}
