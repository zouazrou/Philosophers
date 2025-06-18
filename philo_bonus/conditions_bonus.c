/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:24:00 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 15:32:18 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	fetch_num_meals(philo_t *philo)
{
	int	val;

	sem_wait(philo->sem_meal);
	val = philo->num_meals;
	sem_post(philo->sem_meal);
	return (val);
}

ms_t	fetch_last_meal(philo_t *philo)
{
	ms_t	time;

	sem_wait(philo->sem_meal);
	time = philo->last_meal;
	sem_post(philo->sem_meal);
	return (time);
}
