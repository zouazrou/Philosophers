#include "Philosophers.h"


void	sleeping(data_t *data, int id)
{
	pthread_mutex_lock(&data->write);
	printf("%lld %d is sleeping\n", get_time_difference(data), id);
	pthread_mutex_unlock(&data->write);
	usleep(data->t_sleep);
	pthread_mutex_lock(&data->write);
	printf("%lld %d is thinking\n", get_time_difference(data), id);
	pthread_mutex_unlock(&data->write);
}

// void    sleeping(data_t *data, int id)
// {
//     printf("%ld %d is sleeping\n", get_time_difference(data), id+1);
//     usleep(data->t_sleep);
//     thinking(data, id);
// }

// int    eating(philo_t *philo)
// {
// 	static bool	first = true;
// 	int			r;

// 	if ()
// 	{
// 		if (first == true)
// 			first = false;
// 		else
// 			thinking(data, id);
// 		if (data->num_ph%2 == 0)
// 			usleep(data->t_eat);
// 		else
// 			usleep(data->t_eat * 2);
//     }
//     r = (id + 1) % data->num_ph;
//     return (0);
// }

void    *philosopher_life(void *arg)
{
	philo_t	*philo;
	data_t	*data;

	philo = (philo_t *)arg;
	data = (data_t *)philo->data;

	pthread_mutex_lock(&data->write);
	printf("%lld %d is thinking\n", get_time_difference(data), philo->id);
	pthread_mutex_unlock(&data->write);
	sleeping(data, philo->id);
	// pthread_mutex_lock(&data->write);
	// printf("before sleep in thread %d\n", philo->id);
	// pthread_mutex_unlock(&data->write);
	// sleep(1);
	// pthread_mutex_lock(&data->write);
	// printf("after sleep in thread %d\n", philo->id);
	// pthread_mutex_unlock(&data->write);

	return (NULL);
}

int	main(int ac, char *av[])
{
	data_t	data;
	int		i;

	handling_input(&data, ac, av);
	init_arg(&data);
	i = -1;
	// printf("time before create threads -> %lld-%lld\n", get_current_time() - data.start_time, get_current_time());
	data.start_time = get_current_time();
	while (++i < data.num_ph)
	{
		pthread_create(&data.ph[i].th, NULL, philosopher_life, &data.ph[i]);
	}
	data.simulation_stop = true;
	i = -1;
	while (++i < data.num_ph)
	{
		pthread_join(data.ph[i].th, NULL);
	}
	clean_all_resource(&data);
	// while (!arg.simulation_stop)
	// {
	// 	i = -1;
	// 	while (++i < arg.num_ph)
	// 	{
	// 		if (get_time_difference(&arg) - arg.ph[i].last_meal > arg.t_die)
	// 		{
	// 			arg.simulation_stop = true;
	// 			printf("%ld %d died\n", get_time_difference(&arg), i + 1);
	// 			break;
	// 		}
	// 	}
	// }
    return (0);
}
