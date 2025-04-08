#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#define	UNAVAILABLE -42

typedef struct      ph_s
{
	int				id;
	pthread_t       th;
	long long		last_meal;
    pthread_mutex_t         *r_fork;
    pthread_mutex_t         *l_fork;
}                   ph_t;

typedef struct      data_s
{
    int             num_ph;   			// ok
    long long		t_die;    			// ok
    long long		t_eat;  			// ok
    long long		t_sleep;  			// ok
    int				nb_meals;  			// ok
    long long		start_time;
    ph_t            *ph;				// ok
	pthread_mutex_t	*forks;				// ok
    bool            simulation_start;
	bool			simulation_stop;
}                   data_t;

// utils
long long	ft_atoi_plus(const char *nptr);
long		timedifference_msec(data_t *data);
void		clean_all_resource(data_t	*arg);

// main functions
void		handling_input(data_t *phs, int ac, char **av);
void		init_arg(data_t *arg);

#endif
