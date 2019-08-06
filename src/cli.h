/**
 * cli.h
 *
 * Holds functionality for parsing cmdline args into
 * a workable struct
 */

#ifndef __CLI__H_
#define __CLI__H_

#include "state.h"
#include "data.h"
#include "core.h"
#include "outputter.h"
#include "error.h"
#include "mapper.h"
#include "reader.h"
#include <stdio.h>

/* Returns a banter state struct from given args */
struct banter_state *cli_getstate_fromargs(int argc, char *argv[]);

/* CLI user interface loop */
void cli_ui_loop(struct banter_state *state, struct banter_data *data);

#endif
