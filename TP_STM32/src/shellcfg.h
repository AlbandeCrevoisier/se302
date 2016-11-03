/* Shell configuration file */
#ifndef SHELLCFG_H
#define SHELLCFG_H

extern thread_t *shell_p;

void shell_init(void);
thread_t* shell_spawn(void);

#endif /* SHELLCFG_H */
