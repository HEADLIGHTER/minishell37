#include <stdio.h>
int main()
{
	int i = 0;
	char *str = "mini$hell37: execve: ";
	while (str[i])
		i++;
	printf("%d\n", i);
	return (0);
}
