#include "main.h"

#include <sys/types.h>
#include <dirent.h>

char *dirp_to_name(DIR *dirp)
{
	int fd = dirfd(dirp);
	char *ret = malloc(256);

	char buff[562];
	sprintf(buff, "/proc/self/fd/%d", fd);

	int len = readlink(buff, ret, 256);
	if (len == -1) {
		err("readlink(%s): %s", buff, strerror(errno));
		free(ret);
		return NULL;
	}
	ret[len] = 0;

	return ret;
}

defun(DIR *, opendir, const char *name)
{
	DIR *ret;
	origin(opendir);

	if (!access_file(name)) {
		ret = NULL;
		errno = ENOENT;
	} else {
		ret = orig_opendir(name);
	}

	dbg("opendir(%s) = %p\n", name, ret);

	return ret;
}

defun(struct dirent *, readdir, DIR *dirp)
{
	struct dirent * ret;
	char *path;
	origin(readdir);

	path = dirp_to_name(dirp);
	ret = orig_readdir(dirp);

	if (!ret)
		goto exit;

	path = realloc(path, strlen(path) + strlen(ret->d_name) + 2);
	strcat(path, "/");
	strcat(path, ret->d_name);

	if (!access_file(path))
		ret = readdir(dirp);

exit:
	if (ret)
		dbg("readdir(%p) = {.d_name = %s}\n", dirp, ret->d_name);
	else
		dbg("readdir(%p) = %p\n", dirp, ret);

	free(path);
	return ret;
}

defun(struct dirent64 *, readdir64, DIR *dirp)
{
	struct dirent64 * ret;
	char *path;
	origin(readdir64);

	path = dirp_to_name(dirp);
	ret = orig_readdir64(dirp);

	if (!ret)
		goto exit;

	path = realloc(path, strlen(path) + strlen(ret->d_name) + 2);
	strcat(path, "/");
	strcat(path, ret->d_name);

	if (!access_file(path))
		ret = readdir64(dirp);

exit:
	if (ret)
		dbg("readdir(%p) = {.d_name = %s}\n", dirp, ret->d_name);
	else
		dbg("readdir(%p) = %p\n", dirp, ret);

	free(path);
	return ret;
}
