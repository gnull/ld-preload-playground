#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR *dir;
	struct dirent *ent;

	dir = opendir(".");

	ent = readdir(dir);

	printf("dirent {\n"
	       "  d_name = %s\n"
	       "}\n", ent->d_name);
}
