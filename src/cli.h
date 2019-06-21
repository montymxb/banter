/**
 * cli.h
 *
 * Holds functionality for parsing cmdline args into
 * a workable struct
 */

#ifndef __cli__h_
#define __cli__h_

#include "state.h"
#include <stdio.h>

/* Returns a banter state struct from given args */
struct banter_state *cli_getstate_fromargs(int argc, char *argv[]);

#endif __cli__h_
