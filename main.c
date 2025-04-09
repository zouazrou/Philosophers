#include "Philosophers.h"


void    thinking(philo_t *philo)
{

	pthread_mutex_lock(&((data_t *)philo->data)->write);
	printf("%lld %d is thinking\n", get_time_difference((data_t *)philo->data), philo->id);
	pthread_mutex_unlock(&((data_t *)philo->data)->write);
	usleep(((data_t *)philo->data)->t_sleep);
}

// void    sleeping(data_t *data, int id)
// {
//     printf("%ld %d is sleeping\n", get_time_difference(data), id+1);
//     usleep(data->t_sleep);
//     thinking(data, id);
// }

// int    eating(data_t *data, int id)
// {
// 	static bool	first = true;
//     int r;

// 	printf("test eating\n");
// 	return (3);
//     if (data->ph[id].flag == false)
//     {
//         data->ph[id].flag = true;
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
//     data->ph[id].flag = false;
//     return (0);
// }philosopher

void    *philosopher_life(void *arg)
{
	philo_t	*philo;
	data_t	*data;

	philo = (philo_t *)arg;
	data = (data_t *)philo->data;
	while (!data->simulation_stop)
	{
		thinking(philo);
	}
	// pthread_mutex_lock(&data->write);
	// pthread_mutex_unlock(&data->write);
	return (NULL);
}

int main(int ac, char *av[])
{
	data_t  data;
	int		i;

	handling_input(&data, ac, av);
	init_arg(&data);
	i = -1;
	data.start_time = get_current_time();
	printf("time before create threads -> %lld-%lld\n", get_current_time() - data.start_time, get_current_time());
	while (++i < data.num_ph)
	{
		pthread_create(&data.ph[i].th, NULL, philosopher_life, &data.ph[i]);
		pthread_mutex_lock(&data.write);
		printf("before join id = %lu\n", data.ph[i].th);
		pthread_mutex_unlock(&data.write);
	}
	printf("finish\n");
	usleep(1000);
	data.simulation_stop = true;
	i = -1;
	while (++i < data.num_ph)
	{
		pthread_join(data.ph[i].th, NULL);
		pthread_mutex_lock(&data.write);
		printf("after join id = %lu\n", data.ph[i].th);
		pthread_mutex_unlock(&data.write);
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
