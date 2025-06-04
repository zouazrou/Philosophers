#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SEMA_NAME "/philo"
#define NUM 4
#define NONZERO 42
sem_t	*sem_ptr;

void	Child(int i)
{
	int c = 1000;
	while (c)
	{
		printf("____________________________________xxxxxxxxxxxxxxxxxxxxxxxxx");
		printf("xxxxxxxxx\n");
		usleep(1000000);
	}

	exit(0);
}

int 	main()
{
	pid_t	pid[NUM];
	int		i;

	// create semaphore

	// sem_ptr = sem_open(SEMA_NAME, O_CREAT, S_IRUSR | S_IWUSR, 2);
	// if (sem_ptr == SEM_FAILED)
	// 	printf("fail");

	// Create Child Process
	for (i = 0; i < NUM; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			break;
	}
	if (pid[i] == 0)
	{
		Child(i);
	}

	// Waiting
	if (pid[i])
	{
		for (i = 0; i < NUM; i++)
		{
			waitpid(pid[i], NULL, 0);
		}
	}
	// if (pid[i])
	// 	sem_close(sem_ptr);
	// if (sem_unlink(SEMA_NAME) == -1)
	// 	printf("no sema\n");
	return 0;
}

