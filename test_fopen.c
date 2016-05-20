#include <stdio.h>

int main(int argc, char **argv)
{
	if (!fopen("existent", "r"))
		perror("fopen");

	return 0;
}
