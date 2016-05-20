#define _GNU_SOURCE
#include <dlfcn.h>

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* wrapper definition macros */
#define defun(ret, name, ...)			\
	typedef ret (*name ## _t)(__VA_ARGS__); \
	ret name(__VA_ARGS__)

#define origin(name)				\
	name ## _t orig_ ## name;		\
	orig_ ## name = dlsym(RTLD_NEXT, #name)

/* ansi colors */
#define COLOR(x)   "\033[1;" #x "m"
#define RED        COLOR(31)
#define GREEN      COLOR(32)
#define YELLOW     COLOR(33)
#define BLUE       COLOR(34)
#define UNDERLINE  "\033[4m"
#define RESET      "\033[0m"

/* debug */
#ifdef DEBUG
# define dbg(fmt, ...) fprintf(stderr, YELLOW "debug"  RESET \
			       " :" BLUE fmt RESET, __VA_ARGS__)
#else
# define dbg(...)
#endif

#define err(fmt, ...) fprintf(stderr, RED "error" RESET \
			      " :" UNDERLINE fmt RESET, __VA_ARGS__)

const char *deny[] = {
	"/tmp/hidden_a",
	"/tmp/hidden_b",
	"/tmp/hiddendir",
	NULL
};


int access_full_path(const char *filename)
{
	int i;
	int len = strlen(filename);

	if (filename[len - 1] == '/')
		len--;

	for (i = 0; deny[i]; ++i)
		if (!strcmp(deny[i], filename))
			return 0;

	return 1;
}


int access_file(const char *filename)
{
	int err;
	char *resolved;

	resolved = realpath(filename, NULL);
	if (!resolved) {
		err("realpath: %s\n",strerror(errno));
		return 0;
	}

	err = access_full_path(resolved);
	free(resolved);

	return err;
}


defun(int, open, const char *path, int flags, ...)
{
	int err;
	origin(open);

	if (!access_file(path)) {
		errno = ENOENT;
		err = -1;
	} else {
		err = orig_open(path, flags);
	}

	dbg("open(%s, 0x%x) = %d\n", path, flags, err);

	return err;
}


defun(int, open64, const char *path, int flags, ...)
{
	int err;
	origin(open64);

	if (!access_file(path)) {
		errno = ENOENT;
		err = -1;
	} else {
		err = orig_open64(path, flags);
	}

	dbg("open64(%s, 0x%x) = %d\n", path, flags, err);

	return err;
}


defun(FILE *, fopen, const char *path, const char *mode)
{
	FILE* err;
	origin(fopen);

	if (!access_file(path)) {
		errno = ENOENT;
		err = NULL;
	} else {
		err = orig_fopen(path, mode);
	}

	dbg("fopen(%s, \"%s\") = %p\n", path, mode, err);

	return orig_fopen(path, mode);
}

