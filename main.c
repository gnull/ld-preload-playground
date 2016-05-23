#include "main.h"

const char *deny[] = {
	"/tmp/denied_1",
	"/tmp/denied_2",
	NULL
};

void __attribute__((__constructor__)) overlay_init(void)
{
	dbg("overlay.so started! LD_PRELOAD = %s\n", getenv("LD_PRELOAD"));
}
