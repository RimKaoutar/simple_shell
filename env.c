#include "shell.h"

int _setenv(char *env_name, char *env_value, bool modify)
{
	extern char **environ;
	int i = 0, len_env_name = 0;
	char *new_env;

	if (!env_name || !env_value)
	{
		return (-1);
	}
	while (environ[i])
	{
		len_env_name = _strlen(env_name);
		if (_strncmp(environ[i], env_name, len_env_name) == 0)
		{
			if (modify)
			{
				new_env = malloc(len_env_name + _strlen(env_value) + 2);
				_strcpy(new_env, env_name);
				_strcat(new_env, "=");
				_strcat(new_env, env_value);
				environ[i] = new_env;
				free(new_env);
				return(0);
			}
			return (0);
		}
		i++;
	}
	new_env = malloc(len_env_name + _strlen(env_value) + 2);
	_strcpy(new_env, env_name);
	_strcat(new_env, "=");
	_strcat(new_env, env_value);
	environ[i] = new_env;
	environ[i + 1] = NULL;
	free(new_env);
	return(0);
}
