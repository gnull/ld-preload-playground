#include "main.h"

defun(int, open, const char *path, int flags, mode_t mode)
{
	int ret;
	origin(open);

	if (!access_file(path)) {
		errno = ENOENT;
		ret = -1;
	} else {
		ret = orig_open(path, flags, mode);
	}

	dbg("open(%s, 0x%x) = %d\n", path, flags, ret);

	return ret;
}


defun(int, open64, const char *path, int flags, mode_t mode)
{
	int ret;
	origin(open64);

	if (!access_file(path)) {
		errno = ENOENT;
		ret = -1;
	} else {
		ret = orig_open64(path, flags, mode);
	}

	dbg("open64(%s, 0x%x) = %d\n", path, flags, ret);

	return ret;
}


defun(FILE *, fopen, const char *path, const char *mode)
{
	FILE* ret;
	origin(fopen);

	if (!access_file(path)) {
		errno = ENOENT;
		ret = NULL;
	} else {
		ret = orig_fopen(path, mode);
	}

	dbg("fopen(%s, %s) = %p\n", path, mode, ret);

	return orig_fopen(path, mode);
}

