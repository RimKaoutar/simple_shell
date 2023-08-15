#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f;
	int max;

    f = fopen("/proc/sys/kernel/pid_max", "r");
    if (!f)
    {
	    perror("cant open file");
	    return (EXIT_FAILURE);
    }
    fscanf(f, "%d", &max);
    fclose(f);
    printf("Maximum Process ID (PID) Value: %d\n", max);

    return (EXIT_SUCCESS);
}
