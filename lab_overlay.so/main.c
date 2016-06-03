#include "main.h"

const char **deny;

char *copy_string(const char *token)
{
	int len;
	char *res;

	len = strlen(token);
	res = malloc(len + 1);
	strcpy(res, token);

	return res;
}

void __attribute__((__constructor__)) overlay_init(void)
{
	dbg("overlay.so started! LD_PRELOAD = %s\n", getenv("LD_PRELOAD"));

	int deny_size;
	char buff[1000];
	char *token;
	char *env;

	deny = malloc(sizeof(char *));
	deny[0] = NULL;
	deny_size = 1;

	env = getenv("OVERLAY_DENY");
	if (!env) {
		dbg("OVERLAY_DENY %s env not found. Nothing to do.\n", env);
		return;
	}

	strncpy(buff, env, 999);

	token = strtok(buff, ":");
	do {
		dbg("file '%s' will be hidden\n", token);
		deny_size++;
		deny = realloc(deny, deny_size * sizeof(char *));

		deny[deny_size - 2] = copy_string(token);
		deny[deny_size - 1] = NULL;
	} while (token = strtok(NULL, ":"));
}
