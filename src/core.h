/**
 * core.h
 *
 * Holds the core components of banter
 */

#ifndef __CORE__H_
#define __CORE__H_

#include "state.h"
#include "data.h"
#include <stdio.h>

/* Returns a data object for the current state */
void core_getdata_obj_withstate(struct banter_state *state, struct banter_data *data);

#endif __CORE__H_
