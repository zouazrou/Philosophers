#include "Philosophers.h"

void	handling_input(data_t *arg, int ac, char **av)
{
    if (!(ac > 4 && ac < 7))
	{
        exit ((write(2, "Error : number of argments must 5 or 6\n", 40), 1));
	}
	memset(arg, 0, sizeof(data_t));
	arg->num_ph = ft_atoi_plus(av[1]);
    arg->t_die = ft_atoi_plus(av[2]);
    arg->t_eat = ft_atoi_plus(av[3]);
    arg->t_sleep = ft_atoi_plus(av[4]);
    arg->nb_meals = UNAVAILABLE;
	if (ac == 6)
		arg->nb_meals = ft_atoi_plus(av[5]);

}

void	init_arg(data_t *arg)
{
	int	i;

	arg->ph = malloc(arg->num_ph * sizeof(ph_t));
	arg->forks = malloc(arg->num_ph * sizeof(pthread_mutex_t));
    if (!arg->ph || !arg->forks)
	exit((write(2, "Error : malloc\n", 16), 1));
    i = -1;
    while (++i < arg->num_ph)
    {
		arg->ph[i].id = 42;
		memset(arg->ph + i, 0, sizeof(ph_t));
        pthread_mutex_init(&arg->forks[i], NULL);
    }
	i = -1;
    while (++i < arg->num_ph)
	{
		arg->ph[i].r_fork = &arg->forks[(i+1) % arg->num_ph];
		arg->ph[i].l_fork = &arg->forks[i % arg->num_ph];
		printf("ph [%d] l = %d\n", i, i %  arg->num_ph);
		printf("ph [%d] r = %d\n", i, (i+1) % arg->num_ph);
		// arg->ph[i].l_fork = &arg->forks[(i-1) % arg->num_ph];
		// arg->ph[i].r_fork = &arg->forks[i % arg->num_ph];
		// printf("ph [%d] l = %d\n", i, (i-1) % arg->num_ph);
		// printf("ph [%d] r = %d\n", i, i %  arg->num_ph);
	}
}
