/**
 * outputter.h
 *
 * Key components for writing out data to the visualizer
 */

#ifndef __OUTPUTTER__H_
#define __OUTPUTTER__H_

#include "state.h"
#include <stdio.h>

/* Returns a data object for the current state */
void outputter_writedata_withstate(struct banter_data *data, struct banter_state *state);

#endif
