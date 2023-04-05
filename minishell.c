#include "minishell.h"

void	get_envvariables(t_env *env)
{
	int	i;

	i = 0;	
	env->user = getenv("USER");
	env->home = getenv("HOME");
	env->local = getenv("SESSION_MANAGER");
	while (*env->local != '/')
		env->local++;
	env->local++;
	while (env->local[i] != '.')
		i++;
	env->local[i] = '\0';
}

int	main(int ac, char **av, char **env)
{
	t_env	envvar;
	char	*cwd;
	char	*input;
	char	*buffer;
	char	*trimcwd;
	int		i = 0;

	get_envvariables(&envvar);
	while (1)
	{
    	cwd = getcwd(0, 0);
		while (cwd[i] == envvar.home[i])
			i++;
		trimcwd = ft_strdup(cwd + i);
    	printf("%s@%s:~%s ", envvar.user, envvar.local, trimcwd);
    	buffer = readline("$");
		printf("%s", buffer);
		free(buffer);
		free(cwd);
		free(trimcwd);
		break;
	}
	return (0);
}
