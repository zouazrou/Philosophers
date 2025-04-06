#include "Philosophers.h"

void parse_handling_err(data_t *arg, int ac, char **av)
{
    int i;
    // bool    err;

    if (ac != 5)
        exit ((printf("Error : arg\n"), 1));
    arg->t_die = ft_atoi(av[2]);
    arg->t_eat = ft_atoi(av[3]);
    arg->t_sleep = ft_atoi(av[4]);
    arg->num_ph = ft_atoi(av[1]);
    arg->start = false;
	arg->stop = false;
    pthread_mutex_init(&arg->id_lock, NULL);
    arg->ph = malloc(arg->num_ph * sizeof(ph_t));
    if (!arg->ph)
        exit((printf("Error : malloc\n"), 1));
    i = -1;
    while (++i < arg->num_ph && i >= 0)
    {
        arg->ph[i].fork.open = true;
        pthread_mutex_init(&arg->ph[i].fork.lock, NULL);
        arg->ph[i].stutus = THINKING;
		arg->ph[i].last_meal = 0;
        // if (!pthread_mutex_init(&arg->ph[i].lock, NULL))
        //     printf("error in mutex\n");
    }
}
