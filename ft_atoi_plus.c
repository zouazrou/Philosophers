/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_plus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:35:27 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/08 13:35:04 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

long long	ft_atoi_plus(const char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	// while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
	// 	i++;

	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		exit((write(2, "Error : time must be positive (-_-)\n", 37), 1));
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit((write(2, "Error : argument must be digit\n", 32), 1));
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb);
}

// to convert from s to ms : * 1000
// to convert from s to ms : / 1000
long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	clean_all_resource(data_t	*arg)
{
	int	i;

	i = -1;
	free(arg->forks);
	arg->forks = NULL;
	free(arg->ph);
	arg->ph = NULL;

}

// long timedifference_msec(data_t *data)
// {
// 	struct timeval t0;
// 	struct timeval t1;

// 	t0 = data->s_time;
// 	gettimeofday(&t1, NULL);
// 	return (t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000;
// }
