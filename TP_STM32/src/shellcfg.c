/* Shell configuration file */

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"
#include "serialusbcfg.h"

thread_t *shell_p = NULL;

static void cmd_p(BaseSequentialStream *ch_p, int argc, char *argv[]);

static const ShellCommand cmd[] = {
	{"p", cmd_p}
};

static const ShellConfig shell_cfg = {
	(BaseSequentialStream *)&SDU1,
	cmd
};

static void
cmd_p(BaseSequentialStream *ch_p, int argc, char *argv[])
{
	if (argc == 0)
		return;
	chprintf(ch_p, "%s", argv[1]);
}

void
shell_init(void)
{
	shellInit();
}

thread_t*
shell_spawn(void)
{
	return shellCreate(&shell_cfg, THD_WORKING_AREA_SIZE(2048), NORMALPRIO);
}
