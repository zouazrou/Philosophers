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

typedef struct      philo_s
{
	int				id;					// ok
	pthread_t       th;					// ok
	long long		last_meal;			// ok
    pthread_mutex_t	*r_fork;			// ok
    pthread_mutex_t	*l_fork;			// ok
	void			*data;				// ok TYPE data_t
}                   philo_t;

typedef struct      data_s
{
    int             num_ph;   			// ok
    long long		t_die;    			// ok
    long long		t_eat;  			// ok
    long long		t_sleep;  			// ok
    int				nb_meals;  			// ok
    long long		start_time;
	pthread_mutex_t	write;  			// ok
    philo_t			*ph;				// ok
	pthread_mutex_t	*forks;				// ok
	bool			simulation_stop;	// ok
}					data_t;

// utils
long long	ft_atoi_plus(const char *nptr);
long long	get_current_time(void);
long long	get_time_difference(data_t *data);
void		clean_all_resource(data_t	*data);

// main functions
void		handling_input(data_t *data, int ac, char **av);
void		init_arg(data_t *data);

#endif
