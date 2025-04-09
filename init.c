#include "Philosophers.h"

void	handling_input(data_t *arg, int ac, char **av)
{
    if (!(ac > 4 && ac < 7))
	{
        exit ((write(2, "Error : number of argments must 5 or 6\n", 40), 1));
	}
	memset(arg, 0, sizeof(data_t));
	arg->num_ph = ft_atoi_plus(av[1]);
    arg->t_die = ft_atoi_plus(av[2]) * 1000;
    arg->t_eat = ft_atoi_plus(av[3]) * 1000;
    arg->t_sleep = ft_atoi_plus(av[4]) * 1000;
    arg->nb_meals = UNAVAILABLE;
	if (ac == 6)
		arg->nb_meals = ft_atoi_plus(av[5]);

}

void	init_arg(data_t *data)
{
	int	i;

	// initualize data struct
	data->ph = malloc(data->num_ph * sizeof(philo_t));
	data->forks = malloc(data->num_ph * sizeof(pthread_mutex_t));
	if (!data->ph || !data->forks)
		exit((write(2, "Error : malloc\n", 16), 1));
	data->simulation_stop = false;
	pthread_mutex_init(&data->write, NULL);
	// initualize philo_t struct
	i = -1;
	while (++i < data->num_ph)
    {
		memset(data->ph + i, 0, sizeof(philo_t));
        pthread_mutex_init(&data->forks[i], NULL);
		data->ph[i].r_fork = &data->forks[(i+1) % data->num_ph];
		data->ph[i].l_fork = &data->forks[i % data->num_ph];
		data->ph[i].id = i + 1;
		data->ph[i].data = data;
		// printf("ph [%d] l = %d\n", data->ph[i].id, i %  data->num_ph);
		// printf("ph [%d] r = %d\n", data->ph[i].id, (i+1) % data->num_ph);
	}
}
