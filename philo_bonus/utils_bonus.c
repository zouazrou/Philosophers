/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 18:57:58 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_ms	ft_atoi_plus(const char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		exit((ft_putendl_fd("Error : time must be positive (-_-)", 2),
				EXIT_FAILURE));
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit((ft_putendl_fd("Error : argument must be digit", 2),
					EXIT_FAILURE));
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb);
}

t_ms	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc((ft_strlen(s) + 1));
	if (p == NULL)
		return (p);
	while (i < ft_strlen(s) + 1)
	{
		*(p + i) = s[i];
		i++;
	}
	return (p);
}
