#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	(void)ac;

	while (*av)
	{
		printf("%s\n", *av++);	
	}
	return (0);

}
