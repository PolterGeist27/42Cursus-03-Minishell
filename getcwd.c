#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{

	//Using getcwd this way is not necessary to free anything
	// char	buffer[100];
	// char	*path;

	// path = getcwd(buffer, 100);
	// printf("path = %s\n", path);
	// printf("buf = %s\n", buffer);


	//In other hand, this way the buffer is allocated dinamically and is returned.
	//So it is necessary to free up the returned string.
	char	*path;
	path = getcwd(NULL, 0);
	printf("path = %s\n", path);
	free(path);

	chdir("/home/fvalli-v/Documents/42Cursus");

	path = getcwd(NULL, 0);
	printf("path = %s\n", path);
	free(path);

	return (0);
}