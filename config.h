#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Configuration Macros */
#define BUF_SIZE 1024
#define BUF_FLUSH -1
#define HISTORY_FILE ".simple_shell_history"
#define MAX_HIST_COUNT 4096

/* Flags */
#define CHAIN_CMD 3
#define AND_CMD 2
#define OR_CMD 1
#define NORM_CMD 0

/* Conversion Flags */
#define TO_LOWERCASE 1
#define TO_UNSIGNED 2

/* External Variables */
extern char **environ;

#endif
