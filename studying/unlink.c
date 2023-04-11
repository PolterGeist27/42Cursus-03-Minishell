#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>

int	main(void) {
  int fd;
  char fn[]="./unlink.txt";

  if ((fd = open(fn, O_RDONLY | O_CREAT)) < 0)
    perror("creat() error");
  else {
    close(fd);
    if (unlink(fn) != 0)
      perror("unlink() error\n");
	else
		printf("unlink sucess!\n");
  }
  return (0);
}