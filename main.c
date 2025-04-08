#include "Philosophers.h"


// void    thinking(data_t *data, int id)
// {
//     printf("%ld %d is thinking\n", timedifference_msec(data), id+1);
// }

// void    sleeping(data_t *data, int id)
// {
//     printf("%ld %d is sleeping\n", timedifference_msec(data), id+1);
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
// }

// void    *phsopher_life(void *arg)
// {
//     static int  idx = 0;
//     int id;
//     data_t  *data;

//     data = (data_t *)arg;
//     pthread_mutex_lock(&data->id_lock);
//     id = idx++;
//     pthread_mutex_unlock(&data->id_lock);
//     if (id == data->num_ph - 1)
// 	{
//         gettimeofday(&data->s_time, NULL);
//         data->simulation_start = true;
//     }
//     while (!data->simulation_stop)
//     {
//         eating(data, id);
// 		sleeping(data, id);
//     }
//     return (0);
// }

// eating -> sleeping -> thinking->
//   |____________________________|
int main(int ac, char *av[])
{
	data_t  arg;

	handling_input(&arg, ac, av);
	init_arg(&arg);
	// while (i < arg.num_ph)
	// {
	// 	pthread_create(&arg.ph[i++].th, 0, phsopher_life, &arg);
	// }

	// while (!arg.simulation_stop)
	// {
	// 	i = -1;
	// 	while (++i < arg.num_ph)
	// 	{
	// 		if (timedifference_msec(&arg) - arg.ph[i].last_meal > arg.t_die)
	// 		{
	// 			arg.simulation_stop = true;
	// 			printf("%ld %d died\n", timedifference_msec(&arg), i + 1);
	// 			break;
	// 		}
	// 	}
	// }
	// i = 0;
	// while (i < arg.num_ph)
	// 	pthread_detach(arg.ph[i++].th);
	clean_all_resource(&arg);
    return 0;
}
