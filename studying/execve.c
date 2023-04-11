#include <unistd.h>
#include <stdio.h>

int	main(void){
	//awk '{print "Welcome to awk command tutorial "}'
	// char	*argv[] = {"/usr/bin/awk", "{print \"Welcome to awk command tutorial \"}", NULL};
	//awk -F: '{print $1}' /etc/passwd
	// char	*argv[] = {"/usr/bin/awk", "-F:", "{print $1}", "/etc/passwd", NULL};
	// echo "fabio \nvalli \nvieira"
	char	*argv[] = {"/usr/bin/echo", "fabio \nvalli \nvieira", NULL};
	int val = execve(argv[0], argv, NULL);

	if (val == -1)
		perror("Error");

	printf("Done with execve!\n");
	return (0);
}