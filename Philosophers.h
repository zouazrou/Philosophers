#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

#define EATING   1
#define SLEEPING 2
#define THINKING 3
#define DEAD     4

typedef int status_t;

typedef struct      mutex_s
{
    bool            open;
    pthread_mutex_t lock;
}                   mutex_t;

typedef struct      ph_s
{
	long			last_meal;
    pthread_t       th;
    mutex_t         fork;
    bool            flag;
    status_t        stutus;
}                   ph_t;

typedef struct      data_s
{
    int             t_die;    // ok
    int             t_eat;    // ok
    int             t_sleep;  // ok
    int             num_ph;   // ok
    pthread_mutex_t id_lock;
    bool            start;    // ok
    struct timeval  s_time;// ok
    ph_t            *ph;
	bool			stop;
}                   data_t;

// utils
int     ft_atoi(const char *nptr);
void	destroy_all_resource(data_t	*arg);

int     ft_usleep(size_t milliseconds);
// main functions
void    parse_handling_err(data_t *phs, int ac, char **av);

#endif
