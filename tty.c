#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>


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
	char	*buffer;
	term = ttyname(1);
	printf("This is terminal %s\n",term);
	printf("Return from ttyslot(): %d\n",ttyslot());

    return(0);
}