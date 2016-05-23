#define _GNU_SOURCE
#include <dlfcn.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/* Helper macros for defining wrappers */
#define defun(ret, name, ...)			\
	typedef ret (*name ## _t)(__VA_ARGS__); \
	ret name(__VA_ARGS__)

#define origin(name)				\
	name ## _t orig_ ## name;		\
	orig_ ## name = dlsym(RTLD_NEXT, #name)


/* Pretty terminal colors */
#define COLOR(x)   "\033[1;" #x "m"
#define RED        COLOR(31)
#define GREEN      COLOR(32)
#define YELLOW     COLOR(33)
#define BLUE       COLOR(34)
#define UNDERLINE  "\033[4m"
#define RESET      "\033[0m"


#define dbg(fmt, ...) if (getenv("OVERLAY_DEBUG"))		\
		fprintf(stderr, YELLOW "debug"  RESET			\
			" :" BLUE fmt RESET, __VA_ARGS__)

#define err(fmt, ...) fprintf(stderr, RED "error" RESET \
			      " :" UNDERLINE fmt RESET, __VA_ARGS__)

/* List of file paths to be hidden */
extern const char *deny[];
