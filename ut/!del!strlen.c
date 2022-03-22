#include <stdio.h>
int main()
{
	int i = 0;
	char *str = ": command not found\n";
	while (str[i])
		i++;
	printf("%d\n", i);
	return (0);
}
