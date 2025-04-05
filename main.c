#include "Philosophers.h"

long timedifference_msec(struct timeval t0) {
    struct timeval t1;
    
    gettimeofday(&t1, NULL);
    return (t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000;
}

void    thinking(data_t *data, int id)
{
    printf("%ld %d is thinking\n", timedifference_msec(data->s_time), id+1);
}

void    sleeping(data_t *data, int id)
{
    printf("%ld %d is sleeping\n", timedifference_msec(data->s_time), id+1);
    ft_usleep(data->t_sleep);
    thinking(data, id);
}

int    eating(data_t *data, int id)
{
    struct timeval curr_time;
    int r;


    if (data->ph[id].flag == false)
    {
        data->ph[id].flag = true;
        thinking(data, id);
        ft_usleep(data->t_eat);
        return 1;
    }
    r = (id + 1) % data->num_ph;
    pthread_mutex_lock(&data->ph[id].fork.lock);
    printf("%ld %d has taken a fork\n", timedifference_msec(data->s_time), id+1);
    pthread_mutex_lock(&data->ph[r].fork.lock);
    printf("%ld %d has taken a fork\n", timedifference_msec(data->s_time), id+1);

        printf("%ld %d is eating\n", timedifference_msec(data->s_time), id+1);
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
    pthread_mutex_lock(&data->ph[id].fork.lock);
    pthread_mutex_lock(&data->ph[r].fork.lock);
    if ((data->ph[id].fork.open == true && data->ph[r].fork.open == true))
    {
        data->ph[id].fork.open = false;
        data->ph[r].fork.open = false;
        pthread_mutex_unlock(&data->ph[r].fork.lock);
        pthread_mutex_unlock(&data->ph[id].fork.lock);

        gettimeofday(&curr_time, NULL);
        printf("%ld %d has taken a fork\n", timedifference_msec(data->s_time), id+1);
        printf("%ld %d has taken a fork\n", timedifference_msec(data->s_time), id+1);

        printf("%ld %d is eating\n", timedifference_msec(data->s_time), id+1);
        ft_usleep(data->t_eat);

        pthread_mutex_lock(&data->ph[r].fork.lock);
        pthread_mutex_lock(&data->ph[id].fork.lock);
        data->ph[id].fork.open = true;
        data->ph[r].fork.open = true;
    }
    pthread_mutex_unlock(&data->ph[id].fork.lock);
    pthread_mutex_unlock(&data->ph[r].fork.lock);
    // pthread_mutex_unlock(&data->ph[id].fork.lock);
}

void    *phsopher_life(void *arg)
{
    static int  idx = 0;
    int id;
    data_t  *data;
    struct timeval s_time;

    data = (data_t *)arg;
    pthread_mutex_lock(&data->id_lock);
    id = idx++;
    data->ph[id].flag = (id%2);
    pthread_mutex_unlock(&data->id_lock);
    if (id == data->num_ph - 1)
    {
        gettimeofday(&data->s_time, NULL);
        data->start = true;
    }

    while (data->start == false)
        ;
    while (1)
    {
        if (!   eating(data, id))
            sleeping(data, id);
    }
    return (0);
}

// eating -> sleeping -> thinking->
//   |____________________________|
int main(int ac, char *av[])
{
    data_t  arg;

    parse_handling_err(&arg, ac, av);
    for (int i = 0; i < arg.num_ph ; i++)
    {
        pthread_create(&arg.ph[i].th, 0, phsopher_life, &arg);
    }
    for (int i = 0; i < arg.num_ph; i++)
    {
        pthread_join(arg.ph[i].th, 0);
    }
    return 0;
}