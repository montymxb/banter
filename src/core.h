/**
 * core.h
 *
 * Holds the core components of banter
 */

#ifndef __CORE__H_
#define __CORE__H_

#include "state.h"
#include <stdio.h>

/* Returns a data object for the current state */
struct banter_data *core_getdata_withstate(struct banter_state *state);

#endif __CORE__H_
