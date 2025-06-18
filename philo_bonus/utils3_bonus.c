/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:11:03 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:11:27 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	fetch_num_meals(t_philo *philo)
{
	int	val;

	sem_wait(philo->sem_meal);
	val = philo->num_meals;
	sem_post(philo->sem_meal);
	return (val);
}

t_ms	fetch_last_meal(t_philo *philo)
{
	t_ms	time;

	sem_wait(philo->sem_meal);
	time = philo->last_meal;
	sem_post(philo->sem_meal);
	return (time);
}

static void	ft_len(char const *s1, char const *s2, size_t *lens1, size_t *lens2)
{
	*lens1 = ft_strlen(s1);
	*lens2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lens1;
	size_t	lens2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	ft_len(s1, s2, &lens1, &lens2);
	p = malloc(lens1 + lens2 + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < lens2)
	{
		p[i + lens1] = s2[i];
		i++;
	}
	p[i + lens1] = '\0';
	return (p);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
