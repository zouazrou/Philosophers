/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:31:49 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 10:41:08 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

t_ms	ft_atoi_plus(const char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		exit((ft_putendl_fd("Error : time must be positive (-_-)", 2), 1));
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit((ft_putendl_fd("Error : argument must be digit", 2), 1));
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb);
}

void	use_left(t_philo *philo)
{
	if (simulation_is_stop(philo->data) == true)
		return ;
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	use_right(t_philo *philo)
{
	if (simulation_is_stop(philo->data) == true)
		return ;
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
