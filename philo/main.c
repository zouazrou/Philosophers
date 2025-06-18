/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 19:13:24 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_and_join_th(t_data *data, pthread_t *thread_id)
{
	int	i;

	time_simulation();
	if (data->num_ph == 1)
	{
		pthread_create(thread_id, NULL, single_philosopher, data->philosopher);
		pthread_join(*thread_id, NULL);
		return ;
	}
	i = -1;
	while (++i < data->num_ph)
	{
		pthread_create(thread_id + i, NULL, philosopher_life,
			&data->philosopher[i]);
	}
	observer(data);
	i = -1;
	while (++i < data->num_ph)
	{
		pthread_join(thread_id[i], NULL);
	}
}

int	main(int ac, char *av[])
{
	t_data		data;
	t_err		err;
	pthread_t	*thread_id;

	memset(data.addrs, 0, 3 * sizeof(int *));
	err = handling_args(&data, &thread_id, ac, av);
	if (err == EDGE)
		return (EXIT_SUCCESS);
	if (err != NO_ERR)
		return (clean_all_resource(&data, err), EXIT_FAILURE);
	err = allocate_initial(&data);
	if (err != NO_ERR)
		return (clean_all_resource(&data, err), EXIT_FAILURE);
	create_and_join_th(&data, thread_id);
	clean_all_resource(&data, NO_ERR);
	return (EXIT_SUCCESS);
}
