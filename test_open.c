#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main(int argc, char **argv)
{
	if (open("existent", O_CREAT) == -1)
		perror("open");

	return 0;
}
