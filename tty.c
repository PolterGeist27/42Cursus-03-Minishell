#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	// the fd is not a terminal so ttyname return NULL as error
    // char *term;
	// int fd;
	// char fn[]="./unlink.txt";

	// if ((fd = open(fn, O_RDONLY | O_CREAT)) < 0)
    // 	perror("creat() error");
    // term = ttyname(fd);
    // printf("This is terminal %s\n",term);




	//in the below case fd 0 (stdin), 1 (stdout) and 2(stderror) is considered
	//terminal and return a name
	char *term;
	term = ttyname(0);
    printf("This is terminal %s\n",term);

    return(0);
}