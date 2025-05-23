/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:24:00 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/23 19:24:02 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	simulation_stop(data_t *data)
{
	bool	val;
	pthread_mutex_lock(&data->simulation_mutex);
	val = data->simulation;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (val);
}
