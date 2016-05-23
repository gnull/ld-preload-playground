#include "main.h"

static char *join_paths(const char *dir, const char *file)
{
	int lend, lenf;
	char *ret;

	lend = strlen(dir);
	lenf = strlen(file);

	if (file[0] == '/') {
		ret = malloc(lenf + 1);
		strcpy(ret, file);
	} else {
		ret = malloc(lend + lenf + 2);
		strcpy(ret, dir);
		if (strcmp(file, ".")) {
			strcat(ret, "/");
			strcat(ret, file);
		}
	}

	return ret;
}

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
	int ret;
	char *resolved;
	char *dir = get_current_dir_name();

	resolved = join_paths(dir, filename);
	dbg("join_paths(%s, %s) = %s\n", dir, filename, resolved);
	if (!resolved) {
		free(dir);
		return 1;
	}

	ret = access_full_path(resolved);
	free(resolved);
	free(dir);

	return ret;
}

