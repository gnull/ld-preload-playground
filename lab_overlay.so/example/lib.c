#include <stdlib.h>
#include <stdio.h>

int printf(const char *fmt, ...)
{
	fprintf(stderr, "called printf(%s)\n", fmt);
	return 0;
}
