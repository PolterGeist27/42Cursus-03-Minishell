#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;
	char	*home;
	char	*user;
	char	*local;
	char	*input;
	char	*buffer;
	char	*trimcwd;
	int		i = 0;

	user = getenv("USER");
	home = getenv("HOME");
	local = getenv("SESSION_MANAGER");
	while (*local != '/')
		local++;
	local++;
	while (local[i] != '.')
		i++;
	local[i] = '\0';
	while (1)
	{
    	cwd = getcwd(0, 0);
		while (cwd[i] == home[i])
			i++;
		trimcwd = ft_strdup(cwd + i);
    	printf("%s@%s:~%s ", user, local, trimcwd);
    	buffer = readline("$");
		printf("%s", buffer);
		free(buffer);
		free(cwd);
		free(trimcwd);
		break;
	}
	return (0);
}
