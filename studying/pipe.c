#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int	main(void)
{
	int	fd[2];
	if (pipe(fd) == -1)
		return 1;

	int pid1 = fork();
	if (pid1 < 0)
		return 2;

	if (pid1 == 0)
	{
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char	*argv[] = {"/usr/bin/ping", "-c", "5", "google.com", NULL};
		execve(argv[0], argv, NULL);
		//if success everything below is going to be run just by parent
	}

	int	pid2 = fork();
	if (pid2 == -1)
		return (3);

	if (pid2 == 0)
	{
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		char	*argv[] = {"/usr/bin/grep", "rtt", NULL};
		execve(argv[0], argv, NULL);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);
	return (0);
}