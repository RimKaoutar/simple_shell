#include "shell.h"

/*
 * _setenv - sets or modifies an environment variable
 * @env_name: name of the environment variable
 * @env_value: value to set the environment variable to
 * @modify: specifies whether to modify an existing variable or set a new one
 * Return: 0 on success, -1 on error
*/

int _setenv(char *env_name, char *env_value, bool modify)
{
	extern char **environ;
	int i = 0, len_env_name = 0;
	char *new_env;

	if (!env_name || !env_value)
	{
	  	perror("setenv");
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

/*
 * _unsetenv - Removes an environment variable
 * @env_name: The name of the environment variable to remove
 * Return: 0 on success, -1 if variable not found
*/

int _unsetenv(char* env_name) {

  extern char** environ;
  unsigned int i = 0;
  int len;

  if(!env_name) 
  {
	  perror("unsetenv");
	  return -1;
  }

  len = _strlen(env_name);

  while (environ[i]) {

    if(_strncmp(environ[i], env_name, len) == 0) {
      free(environ[i]);

      while(environ[i]) {
        environ[i] = environ[i+1];
        i++;
      }
      environ[i-1] = NULL;
      return 0;
    }
    i++;
  }
  return -1;
}
