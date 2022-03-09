#include <stdio.h>
#include <unistd.h>

typedef struct s_philo
{
	pid_t	pid;
}	t_philo;

void testing(t_philo *philo)
{
	//pid_t pid;

	for (int i = 0; i < 3; i++)
	{
		philo->pid = fork();
      // This printf statement is for debugging purposes
      // getppid(): gets the parent process-id
      // getpid(): get child process-

     	 printf("[%d] [%d] i=%d\n", getppid(), getpid(), i);
		if (philo->pid == 0)
			printf("child process\n");
   	}
   //printf("[%d] [%d] hi\n", getppid(), getpid());
}

int main()
{
	t_philo philo;
	testing(&philo);
}
