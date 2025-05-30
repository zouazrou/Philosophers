/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/30 10:20:09 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int		main(int ac, char *av[])
{
	int			i;
	data_t		data;
	pthread_t	*thread_ids;

	handling_args(&data, &thread_ids, ac, av);
	allocate_initial(&data);
	time_simulation();
	if (data.num_ph == 1)
	{
		pthread_create(thread_ids, NULL, single_philosopher, data.philosopher);
		pthread_join(*thread_ids, NULL);
		clean_all_resource(&data, &thread_ids);
		return (0);
	}
	i = -1;
	while (++i < data.num_ph)
	{
		pthread_create(thread_ids + i, NULL, philosopher_life, &data.philosopher[i]);
	}
	observer(&data);
	i = -1;
	while (++i < data.num_ph)
	{
		pthread_join(thread_ids[i], NULL);
	}
	clean_all_resource(&data, &thread_ids);
	return (0);
}
