#include "Philosophers.h"

long timedifference_msec(data_t *data)
{
	struct timeval t0;
	struct timeval t1;

	t0 = data->s_time;
	gettimeofday(&t1, NULL);
	return (t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000;
}

void    thinking(data_t *data, int id)
{
    printf("%ld %d is thinking\n", timedifference_msec(data), id+1);
}

void    sleeping(data_t *data, int id)
{
    printf("%ld %d is sleeping\n", timedifference_msec(data), id+1);
    ft_usleep(data->t_sleep);
    thinking(data, id);
}

int    eating(data_t *data, int id)
{
	static bool	first = true;
    int r;

    if (data->ph[id].flag == false)
    {
        data->ph[id].flag = true;
		if (first == true)
			first = false;
		else
			thinking(data, id);
		if (data->num_ph%2 == 0)
			ft_usleep(data->t_eat);
		else
			ft_usleep(data->t_eat * 2);
    }
    r = (id + 1) % data->num_ph;
    pthread_mutex_lock(&data->ph[id].fork.lock);
    printf("%ld %d has taken a fork\n", timedifference_msec(data), id+1);
    pthread_mutex_lock(&data->ph[r].fork.lock);
    printf("%ld %d has taken a fork\n", timedifference_msec(data), id+1);

        printf("%ld %d is eating\n", timedifference_msec(data), id+1);
        ft_usleep(data->t_eat);

    pthread_mutex_unlock(&data->ph[r].fork.lock);
    pthread_mutex_unlock(&data->ph[id].fork.lock);
    data->ph[id].flag = false;
    return (0);
}

void    test_eat(data_t *data, int id)
{
    int r;
    struct timeval curr_time;

    r = (id + 1) % data->num_ph;
    // while (!(data->ph[id].fork.open == true && data->ph[r].fork.open == true))
    //     ;
        pthread_mutex_unlock(&data->ph[r].fork.lock);
        pthread_mutex_unlock(&data->ph[id].fork.lock);

        gettimeofday(&curr_time, NULL);
        printf("%ld %d has taken a fork\n", timedifference_msec(data), id+1);
        printf("%ld %d has taken a fork\n", timedifference_msec(data), id+1);

        printf("%ld %d is eating\n", timedifference_msec(data), id+1);
        ft_usleep(data->t_eat);

        pthread_mutex_lock(&data->ph[r].fork.lock);
        pthread_mutex_lock(&data->ph[id].fork.lock);
    // pthread_mutex_unlock(&data->ph[id].fork.lock);
}

void    *phsopher_life(void *arg)
{
    static int  idx = 0;
    int id;
    data_t  *data;

    data = (data_t *)arg;
    pthread_mutex_lock(&data->id_lock);
    id = idx++;
    pthread_mutex_unlock(&data->id_lock);
    if (id == data->num_ph - 1)
	{
        gettimeofday(&data->s_time, NULL);
        data->start = true;
    }

    while (data->start == false)
        ;
    while (!data->stop)
    {
        eating(data, id);
		sleeping(data, id);
    }
    return (0);
}

// eating -> sleeping -> thinking->
//   |____________________________|
int main(int ac, char *av[])
{
	int		i;
    data_t  arg;
	arg = (data_t){0};
    parse_handling_err(&arg, ac, av);
	i = 0;
    while (i < arg.num_ph)
	{
		arg.ph[i].flag = (i % 2);
        pthread_create(&arg.ph[i++].th, 0, phsopher_life, &arg);
	}
	i = 0;
	while (i < arg.num_ph)
		pthread_detach(arg.ph[i++].th);
	while (!arg.stop)
	{
		i = -1;
		while (++i < arg.num_ph)
		{
			if (timedifference_msec(&arg) - arg.ph[i].last_meal > arg.t_die)
			{
				arg.stop = true;
				printf("%ld %d died\n", timedifference_msec(&arg), i + 1);
				break;
			}
		}
	}
	destroy_all_resource(&arg);
    return 0;
}
