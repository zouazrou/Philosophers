/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:01:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char *av[])
{
	t_data	data;

	handling_args(&data, ac, av);
	unlink_semaphore(&data);
	allocate_initial(&data);
	create_process(&data);
	sem_wait(data.kill);
	kill_process(&data);
	clean_all_resource(&data, NO_ERR);
	return (EXIT_SUCCESS);
}
