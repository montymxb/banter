/**
 * cli.h
 *
 * Holds functionality for parsing cmdline args into
 * a workable struct
 */

#ifndef __cli__h_
#define __cli__h_

#include "state.h"
#include "data.h"
#include "core.h"
#include "outputter.h"
#include <stdio.h>

/* Returns a banter state struct from given args */
struct banter_state *cli_getstate_fromargs(int argc, char *argv[]);

/* CLI user interface loop */
void cli_ui_loop(struct banter_state *state, struct banter_data *data);

#endif __cli__h_
